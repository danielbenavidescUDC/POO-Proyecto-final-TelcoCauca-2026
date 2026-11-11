#ifndef CONSOLA_H
#define CONSOLA_H

#include <mutex>
#include <string>
using namespace std;

extern mutex mtxConsola;
void imprimir(const string& mensaje);

#endif
