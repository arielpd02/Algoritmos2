
template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr),_cardinal(0) {// Completar
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruirNodos(_raiz);
    _raiz = nullptr;
    _cardinal=0;
    // Completar

}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* actual =_raiz;
    while(actual!=nullptr){
        if(actual->valor == clave){
            return true;
        }else{
            if(actual->valor > clave){
                actual=actual->izq;
            }else{
                actual=actual->der;
            }
        }
    }
    return false;
    assert(false);
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {

    if(pertenece(clave))
        return;

    Nodo* nuevo = new Nodo(clave);
    if(_raiz == nullptr){
        _raiz=nuevo;
        _cardinal++;
        return;
    }
    Nodo* actual = _raiz;
    Nodo* padre = actual;
    while(actual!= nullptr){
        if(actual->valor == clave) {
            return; //Ya existía
        }else{
            if (actual->valor > clave) {
                padre=actual;
                actual = actual->izq;
            } else {
                padre=actual;
                actual = actual->der;
            }
        }
    }
    if(padre->valor > clave){
        padre->izq=nuevo;
    }else{
        padre->der=nuevo;
    }
    _cardinal++;
    //assert(false);
}

template<class T>
typename Conjunto<T>::Nodo* Conjunto<T>::predInmediato(Conjunto::Nodo *r) {
    while(r->der!= nullptr){
        r=r->der;
    }
    return r;
}

template<class T>
void Conjunto<T>::eliminarCopia(Conjunto::Nodo *r,T& elem){
    Nodo* actual=r->izq;
    Nodo* padre=actual;
    while(actual->valor!=elem){
        padre=actual;
        actual= actual->der;
    }
    if(padre == actual){  //Caso predecesor raíz del subarbol
        if(actual->izq != nullptr){
            r->izq=actual->izq;
        }else{
            r->izq= nullptr;
        }
        delete actual;
    }else{
        if(actual->izq != nullptr){ //Caso predecesor con subarbol izquierdo
            padre->der=actual->izq;
        }else{
            padre->der= nullptr;    //Caso predecesor hoja
        }
        delete actual;
    }
}

template <class T>
void Conjunto<T>::remover(const T& elem) {

    //Si no pertenece , nada.
    if(!pertenece(elem))
        return;

    if(_cardinal==1){ //Caso arbol de h=1
        delete _raiz;
        _raiz= nullptr;
        _cardinal=0;
        return;
    }

    Nodo* actual=_raiz;
    Nodo* padre = actual;
    while(actual!=nullptr){         //Busco el nodo del elemento a remover
        if(actual->valor == elem){
            break;
        }else{
            if(actual->valor > elem){
                padre=actual;
                actual=actual->izq;
            }else{
                padre=actual;
                actual=actual->der;
            }
        }
    }

    //Caso 1 - nodo hoja
    if(actual->izq == nullptr && actual->der == nullptr){
        if(padre->valor > actual->valor){
            padre->izq = nullptr;
        }else{
            padre->der= nullptr;
        }
        delete actual;
        _cardinal--;

    }else{
        // Caso 2a - nodo con un solo hijo derecho
        if(actual->izq == nullptr){
            if(actual==_raiz){ //Subcaso nodo raíz con hijo derecho
                _raiz=actual->der;
            }else {
                if (padre->valor > elem) {
                    padre->izq = actual->der;
                } else {
                    padre->der = actual->der;
                }
            }
            delete actual;
            _cardinal--;
        }else{
            // Caso 2b - nodo con un solo hijo izquierdo
            if(actual->der == nullptr){
                if(actual==_raiz){ //Subcaso nodo raíz con hijo izquierdo
                    _raiz=actual->izq;
                }else {
                    if (padre->valor > elem) {
                        padre->izq = actual->izq;
                    } else {
                        padre->der = actual->izq;
                    }
                }
                delete actual;
                _cardinal--;
            }else {
                //Caso 3 - nodo con dos hijos
                Nodo* predecesor = predInmediato(actual->izq);
                actual->valor = predecesor->valor;
                eliminarCopia(actual, predecesor->valor);
                _cardinal--;
            }
        }
    }

}
template<class T>
const T& Conjunto<T>::minimoAux(Conjunto::Nodo *r) const{
    Nodo* actual=r;
    while(actual->izq != nullptr){
        actual=actual->izq;
    }
    return (actual->valor);
}

//Precondicion: existe tal el elem.parámetro y tambien hay un siguiente en orden
template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    //Si esta en el subarbol derecho
    if(clave > _raiz->valor){
        Nodo* actual=_raiz;
        Nodo* previo=actual;
        while(actual!= nullptr){   //Busco el elemento
            if(actual->valor == clave){
                break;
            }else{
                if(actual->valor > clave){
                    previo=actual;
                    actual=actual->izq;
                }else{
                    previo=actual;
                    actual=actual->der;
                }
            }
        }
        if(actual->der == nullptr){ //Si es hijo
            return (previo->valor);
        }else{                      //Si es padre
            return (minimoAux(actual->der));
        }
    }else{
    //Si esta en el subarbol izquierdo
    Nodo* actual=_raiz;
    Nodo* seed=actual;
    while(actual->valor != clave){
        if(actual->valor > clave){
            seed=actual;
            actual=actual->izq;
        }else{
            actual=actual->der;
        }
    }
    if(actual->der != nullptr){
        return (actual->der->valor);
    }else{
        return seed->valor;
    }

    }
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* actual=_raiz;
    while(actual->izq!= nullptr){
        actual=actual->izq;
    }
    return (actual->valor);
    assert(false);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* actual=_raiz;
    while(actual->der!= nullptr){
        actual=actual->der;
    }
    return (actual->valor);
    assert(false);
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cardinal;
    assert(false);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
void Conjunto<T>::destruirNodos(Nodo* raiz){
    if(raiz != nullptr){
        destruirNodos(raiz->izq);
        destruirNodos(raiz->der);
        delete raiz;
    }
}

