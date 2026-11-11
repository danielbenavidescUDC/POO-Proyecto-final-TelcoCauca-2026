#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H

#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
private:
    int puertosActivos;

public:
    SwitchFibra(const string& ip, const string& marca, int puertosActivos);
    ~SwitchFibra() override;
    void transmitir() const override;
    string serializar() const override;
};

#endif
