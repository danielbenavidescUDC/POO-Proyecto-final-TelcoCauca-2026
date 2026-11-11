#ifndef TECNICO_H
#define TECNICO_H

#include <string>
using namespace std;

class Tecnico {
private:
    int idTecnico;
    string nombre;
    string especialidad;

public:
    Tecnico(int idTecnico, const string& nombre, const string& especialidad);
    int getIdTecnico() const;
    string getNombre() const;
    string getEspecialidad() const;
    void setNombre(const string& nombre);
    void setEspecialidad(const string& especialidad);
    void mostrarInformacion() const;
};

#endif
