#ifndef TORRE_H
#define TORRE_H

#include <string>
#include <vector>
using namespace std;

class Antena;

class Torre {
private:
    int idTorre;
    string ubicacion;
    double alturaMetros;
    vector<Antena*> listaAntenas;

public:
    Torre(int idTorre, const string& ubicacion, double alturaMetros);
    void agregarAntena(Antena* antena);
    void mostrarInformacion() const;
};

#endif
