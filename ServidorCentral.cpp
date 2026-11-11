#include "Red.h"
#include "ServidorCentral.h"
#include "ClienteRemoto.h"
#include "ExcepcionNodoRed.h"
#include "Consola.h"
#include <cstring>
#include <memory>

static Socket crearSocketServidor(int tipo, int puerto) {
    Socket fd = socket(AF_INET, tipo, 0);
    if (fd == SOCKET_INVALIDO) {
        throw ExcepcionSocket("Fallo al crear socket");
    }

#ifndef _WIN32
    int opcion = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion));
#endif

    sockaddr_in dir;
    memset(&dir, 0, sizeof(dir));
    dir.sin_family = AF_INET;
    dir.sin_addr.s_addr = INADDR_ANY;
    dir.sin_port = htons(puerto);

    if (::bind(fd, reinterpret_cast<sockaddr*>(&dir), sizeof(dir)) < 0) {
        CERRAR_SOCKET(fd);
        throw ExcepcionSocket("Error en bind() del puerto " + to_string(puerto));
    }
    return fd;
}

ServidorCentral::ServidorCentral(int puertoTCP, int puertoUDP)
    : puertoTCP(puertoTCP), puertoUDP(puertoUDP), sockTCP(SOCKET_INVALIDO),
      sockUDP(SOCKET_INVALIDO), activo(false), numClientes(0), totalTCP(0), totalUDP(0) {}

ServidorCentral::~ServidorCentral() {
    detener();
}

void ServidorCentral::iniciar() {
    sockTCP = crearSocketServidor(SOCK_STREAM, puertoTCP);
    if (listen(sockTCP, 5) < 0) {
        CERRAR_SOCKET(sockTCP);
        throw ExcepcionSocket("Error en listen()");
    }

    try {
        sockUDP = crearSocketServidor(SOCK_DGRAM, puertoUDP);
    } catch (...) {
        CERRAR_SOCKET(sockTCP);
        throw;
    }
    ponerTimeout(sockUDP, 3);

    activo = true;
    hiloAceptador = thread(&ServidorCentral::bucleAceptar, this);
    hiloUDP = thread(&ServidorCentral::bucleUDP, this);
    imprimir("[Servidor] Escuchando TCP " + to_string(puertoTCP) + " y UDP " + to_string(puertoUDP));
}

void ServidorCentral::detener() {
    if (!activo.exchange(false)) {
        return;
    }

       try {
        ClienteRemoto despertar(0, "127.0.0.1", puertoTCP);
        despertar.conectar();
    } catch (const ExcepcionSocket&) {
    }

    hiloAceptador.join();
    hiloUDP.join();
    for (size_t i = 0; i < hilosClientes.size(); i++) {
        hilosClientes[i].join();
    }
    hilosClientes.clear();

    CERRAR_SOCKET(sockTCP);
    CERRAR_SOCKET(sockUDP);
    imprimir("[Servidor] Detenido");
}

void ServidorCentral::bucleAceptar() {
    while (activo) {
        Socket cliente = accept(sockTCP, nullptr, nullptr);
        if (!activo) {
            if (cliente != SOCKET_INVALIDO) {
                char c;
                recv(cliente, &c, 1, 0);
                CERRAR_SOCKET(cliente);
            }
            break;
        }
        if (cliente == SOCKET_INVALIDO) {
            continue;
        }
        numClientes++;
        lock_guard<mutex> lock(mtxClientes);
        hilosClientes.push_back(thread(&ServidorCentral::atenderCliente, this, cliente, numClientes));
    }
}

void ServidorCentral::atenderCliente(Socket cliente, int idCliente) {
    imprimir("[Servidor TCP] Cliente " + to_string(idCliente) + " conectado");
    char buffer[512];

    try {
        while (true) {
            int n = recv(cliente, buffer, sizeof(buffer) - 1, 0);
            if (n == 0) {
                break;
            }
            if (n < 0) {
                throw ExcepcionSocket("Error en recv() del cliente " + to_string(idCliente));
            }
            buffer[n] = '\0';

            string respuesta = "ACK";
            try {
                unique_ptr<DispositivoComunicacion> dispositivo(deserializarDispositivo(buffer));
                dispositivo->transmitir();
                lock_guard<mutex> lock(mtxDatos);
                totalTCP++;
            } catch (const ExcepcionNodoRed& e) {
                imprimir(string("[Servidor TCP] Trama rechazada: ") + e.what());
                respuesta = "NACK";
            }
            send(cliente, respuesta.c_str(), respuesta.size(), FLAGS_ENVIO);
        }
    } catch (const ExcepcionSocket& e) {
        imprimir(e.what());
    }

    CERRAR_SOCKET(cliente);
    imprimir("[Servidor TCP] Cliente " + to_string(idCliente) + " desconectado");
}

void ServidorCentral::bucleUDP() {
    TramaTelemetria trama;
    sockaddr_in remitente;

    try {
        while (true) {
            TamanoDir largo = sizeof(remitente);
            int bytes = recvfrom(sockUDP, reinterpret_cast<char*>(&trama), sizeof(trama), 0,
                                 reinterpret_cast<sockaddr*>(&remitente), &largo);
            if (bytes < 0) {
                int err = ultimoError();
                if (esTimeout(err)) {
                    throw ExcepcionRedUDP("TIMEOUT: No se recibio datagrama", err);
                }
                throw ExcepcionRedUDP("ERROR CATASTROFICO UDP", err);
            }
            if (bytes == sizeof(TramaTelemetria)) {
                {
                    lock_guard<mutex> lock(mtxDatos);
                    totalUDP++;
                }
                imprimir("[UDP RX] Estacion: " + to_string(trama.idEstacion) + " (" +
                         string(trama.tipoDispositivo) + ") Temp: " + to_string(trama.temperatura) + "C");
            }
        }
    } catch (const ExcepcionRedUDP& e) {
        imprimir(string("[Servidor UDP] ") + e.what());
    }
}

int ServidorCentral::getTotalTCP() {
    lock_guard<mutex> lock(mtxDatos);
    return totalTCP;
}

int ServidorCentral::getTotalUDP() {
    lock_guard<mutex> lock(mtxDatos);
    return totalUDP;
}
