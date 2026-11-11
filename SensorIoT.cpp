#include "SensorIoT.h"
#include "ExcepcionNodoRed.h"
#include "Consola.h"
#include <iostream>

SensorIoT::SensorIoT(const string& tipoSensor, double valorLectura)
    : tipoSensor(tipoSensor), valorLectura(valorLectura) {
    if (valorLectura < -50.0 || valorLectura > 100.0) {
        throw ExcepcionNodoRed("Lectura fuera de rango: " + to_string(valorLectura));
    }
    cout << "  Constructor SensorIoT " << tipoSensor << endl;
}

SensorIoT::~SensorIoT() {
    cout << "  Destructor SensorIoT " << tipoSensor << endl;
}

void SensorIoT::monitorearCanal(int id, double& lecturaActual) {
    try {
        lecturaActual = valorLectura - 10.0 * id;
        if (lecturaActual < 0) {
            throw runtime_error("Lectura negativa en el canal " + to_string(id));
        }
        imprimir("Sensor " + tipoSensor + ", canal " + to_string(id) + ": " + to_string(lecturaActual));
    } catch (const exception& e) {
        imprimir(string("Excepcion capturada en el hilo: ") + e.what());
    }
}
