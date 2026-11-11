#ifndef DISPOSITIVOCOMUNICACION_H
#define DISPOSITIVOCOMUNICACION_H

#include <string>
#include "ITransmisible.h"
using namespace std;

class DispositivoComunicacion : public ITransmisible {
protected:
    string ip;
    string marca;

public:
    DispositivoComunicacion(const string& ip, const string& marca);
    virtual ~DispositivoComunicacion() = default;
    virtual void transmitir() const = 0;
};

#endif
