#include "GatewayLoRa.h"
#include "Consola.h"
#include <iostream>

GatewayLoRa::GatewayLoRa(const string& ip, const string& marca, double frecuenciaMHz)
    : DispositivoComunicacion(ip, marca), frecuenciaMHz(frecuenciaMHz) {}

GatewayLoRa::~GatewayLoRa() {
    imprimir("Destruyendo GatewayLoRa " + ip);
}

void GatewayLoRa::transmitir() const {
    lock_guard<mutex> lock(mtxConsola);
    cout << "[Gateway LoRa] Paquete LoRaWAN a " << frecuenciaMHz << " MHz. IP: "
         << ip << " (" << marca << ")" << endl;
}

string GatewayLoRa::serializar() const {
    return "GATEWAY|" + ip + "|" + marca + "|" + to_string(frecuenciaMHz);
}
