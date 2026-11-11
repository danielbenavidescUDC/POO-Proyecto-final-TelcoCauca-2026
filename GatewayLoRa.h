#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H

#include "DispositivoComunicacion.h"

class GatewayLoRa : public DispositivoComunicacion {
private:
    double frecuenciaMHz;

public:
    GatewayLoRa(const string& ip, const string& marca, double frecuenciaMHz);
    ~GatewayLoRa() override;
    void transmitir() const override;
    string serializar() const override;
};

#endif
