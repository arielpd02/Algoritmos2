#include "Lista.h"
#include <cassert>

Lista::Lista():_prim(nullptr),_ult(nullptr),_longitud(0) {
    // Completar
}

Lista::Lista(const Lista& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

Lista::~Lista() {
    destruirNodos();
    // Completar
}

Lista& Lista::operator=(const Lista& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    // Completar
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo = new Nodo(elem, nullptr,_prim);
    if(_prim == nullptr){
        _prim=nuevo;
        _ult=nuevo;
    }else {
        (_prim->previo) = nuevo;
        _prim = nuevo;
    }
    // Incremento longitud por nuevo elemento
    _longitud++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo= new Nodo(elem, nullptr, nullptr);
    if(_prim == nullptr) { //ALIASSING
        _prim = nuevo;
        _ult = nuevo;
        _longitud++;
        return;
    }
    Nodo* actual=_prim;
    while (actual->siguiente!= nullptr){ //Itero hasta el final de la lista
        actual=actual->siguiente;
    }
    actual->siguiente = nuevo;
    nuevo->previo=actual;
    _ult=nuevo;
    _longitud++;
}

void Lista::eliminar(Nat i) { //Aca uso eficiencia con la var _ult

    if(_longitud==1){ //Caso borde lista vacía
        delete _prim;
        _prim= nullptr;
        _ult= nullptr;
        _longitud--;
        return;
    }

    if(i==0){ //Caso borde adelante
        Nodo* nuevoPrim = _prim->siguiente;
        nuevoPrim->previo = nullptr;
        delete _prim;
        _prim=nuevoPrim;
        _longitud--;
        return;
    }

    //Casos intermedio y final
    Nodo* actual=_prim;
    for (int j = 0; j < i; ++j) {
        actual=actual->siguiente;
    }
    Nodo* inferior= (actual->previo);
    Nodo* superior;
    if(actual->siguiente!= nullptr) {
        superior = (actual->siguiente);
        inferior->siguiente=superior;
        superior->previo=inferior;
    }
    else{   //Caso borde atras
        superior= nullptr;
        inferior->siguiente=superior;
    }
   delete actual;
    _longitud--;
}

/*
void Lista::eliminar(Nat i) { //Aca uso eficiencia con la var _ult

    if(_longitud==1){ //Caso borde lista vacía
        delete _prim;
        _prim= nullptr;
        _ult= nullptr;
        _longitud--;
        return;
    }
    if(i==0){ //Caso borde adelante
        Nodo* nuevoPrim = _prim->siguiente;
        nuevoPrim->previo = nullptr;
        delete _prim;
        _prim=nuevoPrim;
        _longitud--;
        return;
    }
    // Caso borde atras
    if(i==(_longitud-1)){
        Nodo* nuevoUlt=_ult->previo;
        nuevoUlt->siguiente= nullptr;
        delete _ult;
        _ult= nuevoUlt;
        _longitud--;
        return;
    }
    //Caso nodo intermedio
    Nodo* actual=_prim;
    for (int j = 0; j < i; ++j) {
        actual=actual->siguiente;
    }
    Nodo* inferior= (actual->previo);
    Nodo* superior= (actual->siguiente);
    inferior->siguiente=superior;
    superior->previo=inferior;
    delete actual;
    _longitud--;
}
*/

int Lista::longitud() const {
    // Completar
    return _longitud;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual=_prim;
    for (int j = 0; j < i; ++j) {
        actual=actual->siguiente;
    }
    return (actual->valor);
    // Completar
    assert(false);
}

int& Lista::iesimo(Nat i) {
    Nodo* actual=_prim;
    for (int j = 0; j < i; ++j) {
        actual=actual->siguiente;
    }
    return (actual->valor);
    // Completar (hint: es igual a la anterior...)
    assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar
}

void Lista::copiarNodos(const Lista &o) {
    Nodo* actual=o._prim;
    while (actual!= nullptr){
        agregarAtras(actual->valor);
        actual=actual->siguiente;
    }
}

void Lista::destruirNodos() {
    Nodo* actual=_prim;
    while(actual!= nullptr){
        Nodo* siguiente=actual->siguiente;
        delete actual;
        actual=siguiente;
    }
    _ult= nullptr;
    _prim= nullptr;
    _longitud=0;
}