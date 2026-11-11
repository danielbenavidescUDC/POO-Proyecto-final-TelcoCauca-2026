#ifndef ITRANSMISIBLE_H
#define ITRANSMISIBLE_H

#include <string>
using namespace std;

class ITransmisible {
public:
    virtual ~ITransmisible() = default;
    virtual string serializar() const = 0;
};

#endif
