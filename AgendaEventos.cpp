#include "AgendaEventos.h"
#include "Consola.h"

void AgendaEventos::registrarYMostrar() {
    {
        lock_guard<mutex> lock(mtx);
        lista.push_back({"Andina link expo 2027",
                         "8 al 11 de marzo de 2027",
                         "Cartagena",
                         "Ingenieria electronica y telecomunicaciones"});
        lista.push_back({"IEEE Colombian Caribbean conference 2027",
                         "15 al 18 de septiembre de 2027",
                         "Cartagena",
                         "Ingenieria en investigacion"});
        lista.push_back({"Conecta Colombia - Colombia Telecom conference 2027",
                         "fecha por confirmar",
                         "Bogota",
                         "Ingenieria en telecomunicaciones"});
    }

    imprimir("[Hilo eventos] Agenda de ingenieria 2027 (" + to_string(lista.size()) + " eventos)");
    for (size_t i = 0; i < lista.size(); i++) {
        imprimir("[Hilo eventos] Evento " + to_string(i + 1) + ": " + lista[i].nombre);
        imprimir("      Cuando : " + lista[i].fecha);
        imprimir("      Donde  : " + lista[i].lugar);
        imprimir("      Tema   : " + lista[i].enfoque);
    }
}

int AgendaEventos::total() {
    lock_guard<mutex> lock(mtx);
    return static_cast<int>(lista.size());
}
