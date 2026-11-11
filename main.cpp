#include "Red.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#include "AgendaEventos.h"
#include "Antena.h"
#include "ClienteRemoto.h"
#include "Consola.h"
#include "DispositivoComunicacion.h"
#include "ExcepcionNodoRed.h"
#include "ExcepcionesRed.h"
#include "GatewayLoRa.h"
#include "NodoRedInteligente.h"
#include "RouterWiFi.h"
#include "SensorIoT.h"
#include "ServidorCentral.h"
#include "SupervisorDispositivos.h"
#include "SwitchFibra.h"
#include "Tecnico.h"
#include "Torre.h"
#include "Tramas.h"
using namespace std;

const int PUERTO_TCP = 5050;
const int PUERTO_UDP = 5051;

void seccion(int numero, const string& texto) {
    cout << "\n##################### PARTE " << numero << ": " << texto << " #####################" << endl;
}

void subtitulo(const string& texto) {
    cout << "\n--> " << texto << endl;
}

void parte1() {
    seccion(1, "INFRAESTRUCTURA FISICA");

    Tecnico t1(1, "Juan Bucheli", "Radiofrecuencia");
    Tecnico t2(2, "Daniel Benavides", "Fibra optica");
    t1.mostrarInformacion();
    t2.mostrarInformacion();

    Antena a1(201, 3600.0, "5G");
    Antena a2(202, 2100.0, "4G");
    Antena a3(203, 3300.0, "5G");
    a1.asignarResponsable(&t1);
    a2.asignarResponsable(&t2);
    a3.asignarResponsable(&t1);

    cout << endl;
    Torre torre(7, "Popayan - Centro", 38.0);
    torre.agregarAntena(&a1);
    torre.agregarAntena(&a2);
    torre.agregarAntena(&a3);
    torre.mostrarInformacion();
}

void parte2() {
    seccion(2, "NODOS INTELIGENTES Y EXCEPCIONES");

    try {
        subtitulo("Creando 2 nodos con la misma IP: ");
        NodoRedInteligente n1("10.20.30.40", "00:1A:2B:3C:4D:01", true, "Temperatura", 28.5, 1, 120);
        NodoRedInteligente n2("10.20.30.40", "00:1A:2B:3C:4D:01", true, "Temperatura", 31.5, 2, 80);

        subtitulo("Datos de cada nodo: ");
        cout << n1 << endl;
        cout << n2 << endl;

        subtitulo("Union de nodos: ");
        NodoRedInteligente suma = n1 + n2;
        cout << suma << endl;

        subtitulo("Intento de union con IP distintas");
        NodoRedInteligente n3("10.20.30.99", "00:1A:2B:3C:4D:03", true, "Humedad", 55.0, 3, 60);
        NodoRedInteligente mala = n1 + n3;
    } catch (const ExcepcionNodoRed& e) {
        cout << "[ExcepcionNodoRed capturada]: " << e.what() << endl;
    }

    subtitulo("Error forzado: lectura fuera de rango (130)");
    try {
        NodoRedInteligente n4("10.20.30.41", "00:1A:2B:3C:4D:04", true, "Temperatura", 130.0, 4, 10);
    } catch (const ExcepcionNodoRed& e) {
        cout << "[ExcepcionNodoRed capturada] " << e.what() << endl;
    }

    subtitulo("Error forzado: IP vacia");
    try {
        NodoRedInteligente n5("", "00:1A:2B:3C:4D:05", true, "Temperatura", 20.0, 5, 10);
    } catch (const ExcepcionNodoRed& e) {
        cout << "[ExcepcionNodoRed capturada] " << e.what() << endl;
    }
}

void procesarTransmision(const DispositivoComunicacion* dev) {
    if (dev == nullptr) {
        throw invalid_argument("Puntero nulo detectado en el contenedor polimorfico");
    }
    dev->transmitir();
}

void parte3() {
    seccion(3, "POLIMORFISMO CON VECTOR DE PUNTEROS");

    vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("192.168.50.1", "Huawei", 2.4, 20));
    red.push_back(new GatewayLoRa("10.10.0.5", "Kerlink", 868.0));
    red.push_back(nullptr);
    red.push_back(new SwitchFibra("172.20.0.2", "Ubiquiti", 16));

    subtitulo("Transmision de cada elemento del vector");
    for (size_t i = 0; i < red.size(); i++) {
        try {
            procesarTransmision(red[i]);
        } catch (const invalid_argument& e) {
            cout << "[invalid_argument capturada] " << e.what() << endl;
        }
    }

    subtitulo("Tramas serializadas: ");
    for (size_t i = 0; i < red.size(); i++) {
        if (red[i] != nullptr) {
            cout << "[TRAMA] " << red[i]->serializar() << endl;
        }
    }

    subtitulo("Liberando memoria... ");
    for (size_t i = 0; i < red.size(); i++) {
        if (red[i] != nullptr) {
            delete red[i];
            red[i] = nullptr;
        }
    }
    red.clear();
}

void parte4() {
    seccion(4, "SUPERVISION EN HILOS Y EVENTOS 2027");

    vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("192.168.60.1", "TP-Link", 5.0, 9));
    red.push_back(new GatewayLoRa("10.10.1.5", "Multitech", 915.0));
    red.push_back(new SwitchFibra("172.20.1.2", "MikroTik", 8));
    red.push_back(nullptr);
    red.push_back(new RouterWiFi("192.168.60.2", "Cisco", 2.4, 4));

    vector<double> lecturas;
    lecturas.push_back(30.0);
    lecturas.push_back(12.0);
    lecturas.push_back(40.0);
    lecturas.push_back(9.0);
    lecturas.push_back(5.0);

    SupervisorDispositivos supervisor;
    AgendaEventos agenda;
    vector<thread> hilos;

    subtitulo("Lanzando un hilo por dispositivo y un hilo para la agenda");
    for (size_t i = 0; i < red.size(); i++) {
        hilos.push_back(thread(&SupervisorDispositivos::supervisar, &supervisor, i, red[i], ref(lecturas[i])));
    }
    thread hiloAgenda(&AgendaEventos::registrarYMostrar, &agenda);

    for (size_t i = 0; i < hilos.size(); i++) {
        hilos[i].join();
    }
    hiloAgenda.join();

    subtitulo("Resultado de la supervision: ");
    cout << "Transmisiones exitosas: " << supervisor.getTamanoBuffer() << " de " << red.size() << " dispositivos" << endl;
    cout << "Paquetes contados con mutex: " << supervisor.getPaquetes() << endl;
    cout << "Eventos 2027 registrados: " << agenda.total() << endl;

    for (size_t i = 0; i < red.size(); i++) {
        delete red[i];
    }

    subtitulo("Sensores con monitorearCanal: ");
    SensorIoT s1("Temperatura", 33.0);
    SensorIoT s2("Humedad", 18.0);
    SensorIoT s3("Presion", 7.0);
    double l1 = 0, l2 = 0, l3 = 0;

    vector<thread> hilosSensores;
    hilosSensores.push_back(thread(&SensorIoT::monitorearCanal, &s1, 0, ref(l1)));
    hilosSensores.push_back(thread(&SensorIoT::monitorearCanal, &s2, 1, ref(l2)));
    hilosSensores.push_back(thread(&SensorIoT::monitorearCanal, &s3, 2, ref(l3)));
    for (size_t i = 0; i < hilosSensores.size(); i++) {
        hilosSensores[i].join();
    }
}

void estacionRemota(int id, DispositivoComunicacion* dispositivo, string tipo, float temp, float hum) {
    try {
        ClienteRemoto cliente(id, "127.0.0.1", PUERTO_TCP);
        cliente.conectar();

        string respuesta = cliente.enviarTrama(dispositivo->serializar());
        imprimir("[Estacion " + to_string(id) + "] Servidor respondio: " + respuesta);

        if (id == 2) {
            respuesta = cliente.enviarTrama("DATOS_CORRUPTOS|123");
            imprimir("[Estacion 2] Trama corrupta, servidor respondio: " + respuesta);
        }
        cliente.desconectar();

        TramaTelemetria trama = crearTrama(id, tipo, temp, hum);
        ClienteRemoto::enviarTelemetriaUDP("127.0.0.1", PUERTO_UDP, trama);
        imprimir("[Estacion " + to_string(id) + "] Telemetria UDP enviada");
    } catch (const ExcepcionSocket& e) {
        imprimir(e.what());
    } catch (const ExcepcionRedUDP& e) {
        imprimir(e.what());
    }
}

void parte5() {
    seccion(5, "RED DISTRIBUIDA TCP Y UDP");

    cout << "Tamano de la trama de telemetria: " << sizeof(TramaTelemetria) << " bytes" << endl;

    RouterWiFi router("192.168.70.1", "Cisco", 5.0, 14);
    GatewayLoRa gateway("10.10.2.5", "Multitech", 915.0);
    SwitchFibra switchF("172.20.2.2", "MikroTik", 12);

    try {
        ServidorCentral servidor(PUERTO_TCP, PUERTO_UDP);
        servidor.iniciar();

        vector<thread> estaciones;
        estaciones.push_back(thread(estacionRemota, 1, &router, "Router-WiFi", 24.0f, 58.0f));
        estaciones.push_back(thread(estacionRemota, 2, &gateway, "Gateway-LoRa", 29.5f, 47.0f));
        estaciones.push_back(thread(estacionRemota, 3, &switchF, "Switch-Fibra", 21.0f, 63.5f));
        for (size_t i = 0; i < estaciones.size(); i++) {
            estaciones[i].join();
        }

        subtitulo("Esperando 3 segundos de timeout del receptor UDP");
        servidor.detener();

        subtitulo("Resumen del servidor central");
        cout << "Tramas TCP validas : " << servidor.getTotalTCP() << endl;
        cout << "Datagramas UDP     : " << servidor.getTotalUDP() << endl;
    } catch (const ExcepcionSocket& e) {
        cout << "[ExcepcionSocket capturada] " << e.what() << endl;
    }
}

int main() {
    try {
        iniciarRed();
        cout << "TELCOCAUCA - Monitoreo de infraestructura de telecomunicaciones e IoT" << endl;
        parte1();
        parte2();
        parte3();
        parte4();
        parte5();
        finalizarRed();
        cout << "\n##################### FIN DEL PROGRAMA #####################" << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
