#ifndef TRAMAS_H
#define TRAMAS_H

#include <cstdint>
#include <string>
#include "DispositivoComunicacion.h"
using namespace std;

#pragma pack(push, 1)
struct TramaTelemetria {
    uint32_t idEstacion;
    char tipoDispositivo[16];
    float temperatura;
    float humedad;
    uint64_t timestamp;
};
#pragma pack(pop)

TramaTelemetria crearTrama(int idEstacion, const string& tipo, float temperatura, float humedad);
DispositivoComunicacion* deserializarDispositivo(const string& trama);

#endif
