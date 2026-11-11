#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion {
private:
    double frecuenciaGHz;
    int usuariosConectados;

public:
    RouterWiFi(const string& ip, const string& marca, double frecuenciaGHz, int usuariosConectados);
    ~RouterWiFi() override;
    void transmitir() const override;
    string serializar() const override;
};

#endif
