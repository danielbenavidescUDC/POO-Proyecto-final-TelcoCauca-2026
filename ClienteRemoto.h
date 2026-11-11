#ifndef CLIENTEREMOTO_H
#define CLIENTEREMOTO_H

#include "Red.h"
#include <string>
#include "Tramas.h"
using namespace std;

class ClienteRemoto {
private:
    int idEstacion;
    string ipServidor;
    int puerto;
    Socket sock;
    bool conectado;

public:
    ClienteRemoto(int idEstacion, const string& ipServidor, int puerto);
    ~ClienteRemoto();
    void conectar();
    string enviarTrama(const string& trama);
    void desconectar();
    static void enviarTelemetriaUDP(const string& ipServidor, int puerto, const TramaTelemetria& trama);
};

#endif
