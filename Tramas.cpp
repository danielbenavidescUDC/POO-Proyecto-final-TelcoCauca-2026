#include "Tramas.h"
#include "ExcepcionNodoRed.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
#include <cstring>
#include <ctime>
#include <sstream>
#include <vector>

TramaTelemetria crearTrama(int idEstacion, const string& tipo, float temperatura, float humedad) {
    TramaTelemetria trama;
    memset(&trama, 0, sizeof(trama));
    trama.idEstacion = idEstacion;
    strncpy(trama.tipoDispositivo, tipo.c_str(), sizeof(trama.tipoDispositivo) - 1);
    trama.temperatura = temperatura;
    trama.humedad = humedad;
    trama.timestamp = time(nullptr);
    return trama;
}

DispositivoComunicacion* deserializarDispositivo(const string& trama) {
    vector<string> partes;
    string parte;
    istringstream ss(trama);
    while (getline(ss, parte, '|')) {
        partes.push_back(parte);
    }

    try {
        if (partes.size() == 5 && partes[0] == "ROUTER") {
            return new RouterWiFi(partes[1], partes[2], stod(partes[3]), stoi(partes[4]));
        }
        if (partes.size() == 4 && partes[0] == "GATEWAY") {
            return new GatewayLoRa(partes[1], partes[2], stod(partes[3]));
        }
        if (partes.size() == 4 && partes[0] == "SWITCH") {
            return new SwitchFibra(partes[1], partes[2], stoi(partes[3]));
        }
    } catch (const exception&) {
        throw ExcepcionNodoRed("Trama con numeros invalidos: " + trama);
    }
    throw ExcepcionNodoRed("Trama desconocida: " + trama);
}
