#ifndef SENSORIOT_H
#define SENSORIOT_H

#include <string>
using namespace std;

class SensorIoT {
protected:
    string tipoSensor;
    double valorLectura;

public:
    SensorIoT(const string& tipoSensor, double valorLectura);
    ~SensorIoT();
    void monitorearCanal(int id, double& lecturaActual);
};

#endif
