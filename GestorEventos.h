#ifndef GESTOREVENTOS_H
#define GESTOREVENTOS_H

#include <mutex>
#include <string>
#include <vector>
using namespace std;

class GestorEventos {
private:
    mutex mtx;
    vector<string> eventos;

public:
    void registrarEventos();
    int total();
};

#endif
