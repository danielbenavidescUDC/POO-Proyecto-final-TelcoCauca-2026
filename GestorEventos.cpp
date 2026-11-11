#include "GestorEventos.h"
#include "Consola.h"

void GestorEventos::registrarEventos() {
    {
        lock_guard<mutex> lock(mtx);
        eventos.push_back("MWC Barcelona 2027 - Barcelona - telecomunicaciones moviles (fecha por confirmar)");
        eventos.push_back("IEEE ICC 2027 - comunicaciones (fecha y sede por confirmar)");
        eventos.push_back("Computex 2027 - Taipei - electronica y computacion (fecha por confirmar)");
    }
    imprimir("Eventos de ingenieria 2027 registrados:");
    for (size_t i = 0; i < eventos.size(); i++) {
        imprimir("  " + to_string(i + 1) + ". " + eventos[i]);
    }
}

int GestorEventos::total() {
    lock_guard<mutex> lock(mtx);
    return static_cast<int>(eventos.size());
}
