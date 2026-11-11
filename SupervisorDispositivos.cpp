#include "SupervisorDispositivos.h"
#include "ExcepcionNodoRed.h"
#include "Consola.h"

SupervisorDispositivos::SupervisorDispositivos() : paquetes(0) {}

void SupervisorDispositivos::supervisar(int id, DispositivoComunicacion* dispositivo, double& lectura) {
    try {
        if (dispositivo == nullptr) {
            throw invalid_argument("Puntero nulo en el vector de dispositivos");
        }
        lectura = lectura - 5.0 * id;
        if (lectura < 0) {
            throw ExcepcionNodoRed("Lectura negativa en el hilo " + to_string(id));
        }
        dispositivo->transmitir();

        for (int i = 0; i < 1000; i++) {
            lock_guard<mutex> lock(mtx);
            paquetes++;
        }
        {
            lock_guard<mutex> lock(mtx);
            buffer.push_back(dispositivo->serializar());
        }
        imprimir("Hilo " + to_string(id) + " termino bien");
    } catch (const ExcepcionNodoRed& e) {
        imprimir(string("Hilo ") + to_string(id) + " - ExcepcionNodoRed: " + e.what());
    } catch (const exception& e) {
        imprimir(string("Hilo ") + to_string(id) + " - Error: " + e.what());
    }
}

int SupervisorDispositivos::getPaquetes() {
    lock_guard<mutex> lock(mtx);
    return paquetes;
}

int SupervisorDispositivos::getTamanoBuffer() {
    lock_guard<mutex> lock(mtx);
    return static_cast<int>(buffer.size());
}
