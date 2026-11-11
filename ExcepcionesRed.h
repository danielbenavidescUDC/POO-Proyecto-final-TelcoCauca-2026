#ifndef EXCEPCIONESRED_H
#define EXCEPCIONESRED_H

#include <stdexcept>
#include <string>
using namespace std;

class ExcepcionSocket : public runtime_error {
public:
    ExcepcionSocket(const string& msg) : runtime_error("[Error] " + msg) {}
};

class ExcepcionRedUDP : public runtime_error {
private:
    int codigoErrno;

public:
    ExcepcionRedUDP(const string& msg, int err)
        : runtime_error(msg + " [Errno: " + to_string(err) + "]"), codigoErrno(err) {}
    int getErrno() const { return codigoErrno; }
};

#endif
