#ifndef RED_H
#define RED_H

// Incluir este archivo antes que <thread> y <mutex>.
// En Windows (Zinjal) enlazar con -lws2_32.

#include <cerrno>
#include <string>
#include "ExcepcionesRed.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef SOCKET Socket;
    typedef int TamanoDir;
    #define SOCKET_INVALIDO INVALID_SOCKET
    #define CERRAR_SOCKET(s) closesocket(s)
    #define FLAGS_ENVIO 0
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    typedef int Socket;
    typedef socklen_t TamanoDir;
    #define SOCKET_INVALIDO (-1)
    #define CERRAR_SOCKET(s) close(s)
    #define FLAGS_ENVIO MSG_NOSIGNAL
#endif

using namespace std;

inline void iniciarRed() {
#ifdef _WIN32
    WSADATA datos;
    if (WSAStartup(MAKEWORD(2, 2), &datos) != 0) {
        throw ExcepcionSocket("WSAStartup fallo");
    }
#endif
}

inline void finalizarRed() {
#ifdef _WIN32
    WSACleanup();
#endif
}

inline int ultimoError() {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}

inline bool esTimeout(int err) {
#ifdef _WIN32
    return err == WSAETIMEDOUT || err == WSAEWOULDBLOCK;
#else
    return err == EAGAIN || err == EWOULDBLOCK;
#endif
}

inline void ponerTimeout(Socket s, int segundos) {
#ifdef _WIN32
    DWORD ms = segundos * 1000;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&ms), sizeof(ms));
#else
    struct timeval tv;
    tv.tv_sec = segundos;
    tv.tv_usec = 0;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif
}

// En Windows se usa inet_addr porque el MinGW de Zinjal no trae inet_pton
inline bool convertirIP(const string& ip, in_addr& destino) {
#ifdef _WIN32
    unsigned long dir = inet_addr(ip.c_str());
    if (dir == INADDR_NONE) {
        return false;
    }
    destino.s_addr = dir;
    return true;
#else
    return inet_pton(AF_INET, ip.c_str(), &destino) == 1;
#endif
}

#endif
