#ifndef ANTENA_H
#define ANTENA_H

#include <string>
#include "Tecnico.h"
using namespace std;

class Antena {
private:
    int idAntena;
    double frecuenciaMHz;
    string tecnologia;
    Tecnico* responsableMantenimiento;

public:
    Antena(int idAntena, double frecuenciaMHz, const string& tecnologia);
    int getIdAntena() const;
    void asignarResponsable(Tecnico* tecnico);
    void mostrarInformacion() const;
};

#endif
