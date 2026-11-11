#ifndef EXCEPCIONNODORED_H
#define EXCEPCIONNODORED_H

#include <stdexcept>
#include <string>
using namespace std;

class ExcepcionNodoRed : public runtime_error {
public:
    ExcepcionNodoRed(const string& mensaje) : runtime_error(mensaje) {}
};

#endif
