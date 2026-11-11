#include "SwitchFibra.h"
#include "Consola.h"
#include <iostream>

SwitchFibra::SwitchFibra(const string& ip, const string& marca, int puertosActivos)
    : DispositivoComunicacion(ip, marca), puertosActivos(puertosActivos) {}

SwitchFibra::~SwitchFibra() {
    imprimir("Destruyendo SwitchFibra " + ip);
}

void SwitchFibra::transmitir() const {
    lock_guard<mutex> lock(mtxConsola);
    cout << "[Switch Fibra] Conmutando paquetes opticos en " << puertosActivos
         << " puertos. IP: " << ip << " (" << marca << ")" << endl;
}

string SwitchFibra::serializar() const {
    return "SWITCH|" + ip + "|" + marca + "|" + to_string(puertosActivos);
}
