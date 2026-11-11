#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H

#include <iostream>
#include <string>
#include "DispositivoRed.h"
#include "SensorIoT.h"
using namespace std;

class NodoRedInteligente : public DispositivoRed, public SensorIoT {
private:
    int idNodo;
    int paquetesProcesados;

public:
    NodoRedInteligente(const string& ip, const string& mac, bool estadoOperativo,
                       const string& tipoSensor, double valorLectura,
                       int idNodo, int paquetesProcesados);
    ~NodoRedInteligente();
    NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
    friend ostream& operator<<(ostream& os, const NodoRedInteligente& nodo);
};

#endif
