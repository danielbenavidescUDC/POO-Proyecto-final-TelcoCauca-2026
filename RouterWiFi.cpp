#include "RouterWiFi.h"
#include "Consola.h"
#include <iostream>

RouterWiFi::RouterWiFi(const string& ip, const string& marca, double frecuenciaGHz, int usuariosConectados)
    : DispositivoComunicacion(ip, marca), frecuenciaGHz(frecuenciaGHz), usuariosConectados(usuariosConectados) {}

RouterWiFi::~RouterWiFi() {
    imprimir("Destruyendo RouterWiFi " + ip);
}

void RouterWiFi::transmitir() const {
    lock_guard<mutex> lock(mtxConsola);
    cout << "[Router WiFi] Trama inalambrica a " << frecuenciaGHz << " GHz para "
         << usuariosConectados << " usuarios. IP: " << ip << " (" << marca << ")" << endl;
}

string RouterWiFi::serializar() const {
    return "ROUTER|" + ip + "|" + marca + "|" + to_string(frecuenciaGHz) + "|" + to_string(usuariosConectados);
}
