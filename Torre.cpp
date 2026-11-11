#include "Torre.h"
#include "Antena.h"
#include <iostream>

Torre::Torre(int idTorre, const string& ubicacion, double alturaMetros)
    : idTorre(idTorre), ubicacion(ubicacion), alturaMetros(alturaMetros) {}

void Torre::agregarAntena(Antena* antena) {
    listaAntenas.push_back(antena);
}

void Torre::mostrarInformacion() const {
    cout << "Torre " << idTorre << " | " << ubicacion << " | " << alturaMetros << " m" << endl;
    for (size_t i = 0; i < listaAntenas.size(); i++) {
        listaAntenas[i]->mostrarInformacion();
    }
}
