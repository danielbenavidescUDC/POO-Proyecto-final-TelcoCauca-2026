#ifndef SUPERVISORDISPOSITIVOS_H
#define SUPERVISORDISPOSITIVOS_H

#include <mutex>
#include <string>
#include <vector>
#include "DispositivoComunicacion.h"
using namespace std;

class SupervisorDispositivos {
private:
    mutex mtx;
    vector<string> buffer;
    int paquetes;

public:
    SupervisorDispositivos();
    void supervisar(int id, DispositivoComunicacion* dispositivo, double& lectura);
    int getPaquetes();
    int getTamanoBuffer();
};

#endif
