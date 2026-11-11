#ifndef AGENDAEVENTOS_H
#define AGENDAEVENTOS_H

#include <mutex>
#include <string>
#include <vector>
using namespace std;

struct Evento {
    string nombre;
    string fecha;
    string lugar;
    string enfoque;
};

class AgendaEventos {
private:
    mutex mtx;
    vector<Evento> lista;

public:
    void registrarYMostrar();
    int total();
};

#endif
