#include "Red.h"
#include "ClienteRemoto.h"
#include <cstring>

ClienteRemoto::ClienteRemoto(int idEstacion, const string& ipServidor, int puerto)
    : idEstacion(idEstacion), ipServidor(ipServidor), puerto(puerto),
      sock(SOCKET_INVALIDO), conectado(false) {}

ClienteRemoto::~ClienteRemoto() {
    desconectar();
}

void ClienteRemoto::conectar() {
    sockaddr_in dir;
    memset(&dir, 0, sizeof(dir));
    dir.sin_family = AF_INET;
    dir.sin_port = htons(puerto);
    if (!convertirIP(ipServidor, dir.sin_addr)) {
        throw ExcepcionSocket("IP del servidor invalida: " + ipServidor);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == SOCKET_INVALIDO) {
        throw ExcepcionSocket("Fallo al crear socket");
    }
    if (connect(sock, reinterpret_cast<sockaddr*>(&dir), sizeof(dir)) < 0) {
        CERRAR_SOCKET(sock);
        sock = SOCKET_INVALIDO;
        throw ExcepcionSocket("Estacion " + to_string(idEstacion) + ": fallo connect()");
    }
    conectado = true;
}

string ClienteRemoto::enviarTrama(const string& trama) {
    if (!conectado) {
        throw ExcepcionSocket("Estacion " + to_string(idEstacion) + " no esta conectada");
    }
    if (send(sock, trama.c_str(), trama.size(), FLAGS_ENVIO) < 0) {
        throw ExcepcionSocket("Estacion " + to_string(idEstacion) + ": error en send()");
    }

    char buffer[64];
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (n <= 0) {
        throw ExcepcionSocket("Estacion " + to_string(idEstacion) + ": error en recv()");
    }
    buffer[n] = '\0';
    return string(buffer);
}

void ClienteRemoto::desconectar() {
    if (conectado) {
        CERRAR_SOCKET(sock);
        conectado = false;
    }
}

void ClienteRemoto::enviarTelemetriaUDP(const string& ipServidor, int puerto, const TramaTelemetria& trama) {
    Socket fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == SOCKET_INVALIDO) {
        throw ExcepcionRedUDP("Fallo al crear socket UDP", ultimoError());
    }

    sockaddr_in destino;
    memset(&destino, 0, sizeof(destino));
    destino.sin_family = AF_INET;
    destino.sin_port = htons(puerto);
    if (!convertirIP(ipServidor, destino.sin_addr)) {
        CERRAR_SOCKET(fd);
        throw ExcepcionRedUDP("IP del servidor invalida", 0);
    }

    int enviados = sendto(fd, reinterpret_cast<const char*>(&trama), sizeof(trama), 0,
                          reinterpret_cast<sockaddr*>(&destino), sizeof(destino));
    int err = ultimoError();
    CERRAR_SOCKET(fd);
    if (enviados < 0) {
        throw ExcepcionRedUDP("Error en sendto()", err);
    }
}
