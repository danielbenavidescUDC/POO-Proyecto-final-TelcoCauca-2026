#include "Antena.h"
#include <iostream>

Antena::Antena(int idAntena, double frecuenciaMHz, const string& tecnologia)
    : idAntena(idAntena), frecuenciaMHz(frecuenciaMHz), tecnologia(tecnologia),
      responsableMantenimiento(nullptr) {}

int Antena::getIdAntena() const { return idAntena; }

void Antena::asignarResponsable(Tecnico* tecnico) {
    responsableMantenimiento = tecnico;
}

void Antena::mostrarInformacion() const {
    cout << "  Antena " << idAntena << " | " << tecnologia << " | " << frecuenciaMHz << " MHz | Responsable: ";
    if (responsableMantenimiento != nullptr) {
        cout << responsableMantenimiento->getNombre();
    } else {
        cout << "sin asignar";
    }
    cout << endl;
}
