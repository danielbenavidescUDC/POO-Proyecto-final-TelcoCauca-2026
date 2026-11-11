#include "DispositivoRed.h"
#include "ExcepcionNodoRed.h"
#include <cstdio>
#include <iostream>

bool DispositivoRed::ipValida(const string& ip) {
    int a, b, c, d;
    char resto;
    if (sscanf(ip.c_str(), "%d.%d.%d.%d%c", &a, &b, &c, &d, &resto) != 4) {
        return false;
    }
    return a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255;
}

DispositivoRed::DispositivoRed(const string& direccionIP, const string& direccionMAC, bool estadoOperativo)
    : direccionIP(direccionIP), direccionMAC(direccionMAC), estadoOperativo(estadoOperativo) {
    if (direccionIP.empty()) {
        throw ExcepcionNodoRed("La direccion IP esta vacia");
    }
    if (!ipValida(direccionIP)) {
        throw ExcepcionNodoRed("Formato de IP invalido: " + direccionIP);
    }
    cout << "  Constructor DispositivoRed " << direccionIP << endl;
}

DispositivoRed::~DispositivoRed() {
    cout << "  Destructor DispositivoRed " << direccionIP << endl;
}
