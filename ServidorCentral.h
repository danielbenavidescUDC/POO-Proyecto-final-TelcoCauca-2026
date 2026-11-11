#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include "Red.h"
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "Tramas.h"
using namespace std;

class ServidorCentral {
private:
    int puertoTCP;
    int puertoUDP;
    Socket sockTCP;
    Socket sockUDP;
    atomic<bool> activo;
    int numClientes;

    thread hiloAceptador;
    thread hiloUDP;
    vector<thread> hilosClientes;
    mutex mtxClientes;

    mutex mtxDatos;
    int totalTCP;
    int totalUDP;

    void bucleAceptar();
    void bucleUDP();
    void atenderCliente(Socket cliente, int idCliente);

public:
    ServidorCentral(int puertoTCP, int puertoUDP);
    ~ServidorCentral();
    void iniciar();
    void detener();
    int getTotalTCP();
    int getTotalUDP();
};

#endif
