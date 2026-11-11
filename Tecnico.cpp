#include "Tecnico.h"
#include <iostream>

Tecnico::Tecnico(int idTecnico, const string& nombre, const string& especialidad)
    : idTecnico(idTecnico), nombre(nombre), especialidad(especialidad) {}

int Tecnico::getIdTecnico() const { return idTecnico; }
string Tecnico::getNombre() const { return nombre; }
string Tecnico::getEspecialidad() const { return especialidad; }

void Tecnico::setNombre(const string& nombre) { this->nombre = nombre; }
void Tecnico::setEspecialidad(const string& especialidad) { this->especialidad = especialidad; }

void Tecnico::mostrarInformacion() const {
    cout << "Tecnico " << idTecnico << ": " << nombre << " (" << especialidad << ")" << endl;
}
