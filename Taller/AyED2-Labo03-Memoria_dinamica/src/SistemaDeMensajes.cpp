#include "SistemaDeMensajes.h"

// Completar...


SistemaDeMensajes::SistemaDeMensajes(): _conns(),_pProxys() {}
/*
SistemaDeMensajes::~SistemaDeMensajes() {
    for (int id = 0; id < 4; ++id) {
        delete _conns[id];
    }
    for (int i = 0; i < _pProxys.size(); ++i) {
        delete _pProxys[i];
    }
}
*/
void SistemaDeMensajes::desregistrarJugador(int id) {
    if (registrado(id)){
        delete _conns[id]; // Borro la memoria asociada a la instancia de Conexion Jugador
        _conns[id] = nullptr;
    }
}

void SistemaDeMensajes::registrarJugador(int id, string ip) {
    desregistrarJugador(id);
    _conns[id]= new ConexionJugador(ip);
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje) {
    _conns[id]->enviarMensaje(mensaje);

}

bool SistemaDeMensajes::registrado(int id) const {
    if (_conns[id] == nullptr) //Puntero asociado a ningun tipo de dato , demas que contiene cierta direccion (no se de que)
        return false;
    return true;
}

string SistemaDeMensajes::ipJugador(int id) const {
    return _conns[id]->ip();
}

SistemaDeMensajes::Proxy* SistemaDeMensajes::obtenerProxy(int id) {
    Proxy* nuevoProxy = new Proxy(&_conns[id]);
    _pProxys.push_back(nuevoProxy);
    return nuevoProxy; //Devuelve un puntero al  proxy creado del jugador
}


//Metodos de Proxy

SistemaDeMensajes::Proxy::Proxy(ConexionJugador** conn): _conn(conn){}

void SistemaDeMensajes::Proxy::enviarMensaje(string msg) {
    (*_conn)->enviarMensaje(msg);
}
