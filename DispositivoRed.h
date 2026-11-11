#ifndef DISPOSITIVORED_H
#define DISPOSITIVORED_H

#include <string>
using namespace std;

class DispositivoRed {
protected:
    string direccionIP;
    string direccionMAC;
    bool estadoOperativo;

public:
    DispositivoRed(const string& direccionIP, const string& direccionMAC, bool estadoOperativo);
    ~DispositivoRed();
    static bool ipValida(const string& ip);
};

#endif
