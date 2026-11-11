#include "Consola.h"
#include <iostream>

mutex mtxConsola;

void imprimir(const string& mensaje) {
    lock_guard<mutex> lock(mtxConsola);
    cout << mensaje << endl;
}
