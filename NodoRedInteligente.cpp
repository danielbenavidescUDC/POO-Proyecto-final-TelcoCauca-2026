#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"

NodoRedInteligente::NodoRedInteligente(const string& ip, const string& mac, bool estadoOperativo,
                                       const string& tipoSensor, double valorLectura,
                                       int idNodo, int paquetesProcesados)
    : DispositivoRed(ip, mac, estadoOperativo), SensorIoT(tipoSensor, valorLectura),
      idNodo(idNodo), paquetesProcesados(paquetesProcesados) {
    cout << "  Constructor NodoRedInteligente " << idNodo << endl;
}

NodoRedInteligente::~NodoRedInteligente() {
    cout << "  Destructor NodoRedInteligente " << idNodo << endl;
}

NodoRedInteligente NodoRedInteligente::operator+(const NodoRedInteligente& otro) const {
    if (direccionIP != otro.direccionIP) {
        throw ExcepcionNodoRed("No se pueden sumar nodos con IP distinta: " + direccionIP + " y " + otro.direccionIP);
    }
    return NodoRedInteligente(direccionIP, direccionMAC, estadoOperativo, tipoSensor,
                              (valorLectura + otro.valorLectura) / 2,
                              idNodo * 1000 + otro.idNodo,
                              paquetesProcesados + otro.paquetesProcesados);
}

ostream& operator<<(ostream& os, const NodoRedInteligente& nodo) {
    os << "Nodo " << nodo.idNodo << " | IP: " << nodo.direccionIP << " | MAC: " << nodo.direccionMAC
       << " | " << nodo.tipoSensor << ": " << nodo.valorLectura
       << " | Paquetes: " << nodo.paquetesProcesados;
    return os;
}
