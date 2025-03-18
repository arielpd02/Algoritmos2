
#include "Diccionario.hpp"

typedef int cantidad;

template<class T>
class Multiconjunto{
public:
    Multiconjunto();
    void agregar(T x);
    int ocurrencias(T x) const;
    bool operator<=(Multiconjunto<T> otro) const; // True <=> el multiconj actual esta incluido en otro
private:
    Diccionario<T,cantidad> _diccionario;
};

template<class T>
Multiconjunto<T>::Multiconjunto(): _diccionario() {}

template<class T>
void Multiconjunto<T>::agregar(T x) {
    if(!_diccionario.def(x)){
        _diccionario.definir(x,1); //Definilo con 1 como #ocurrencias del elem
    } else {
        cantidad cantidadIncrementada = _diccionario.obtener(x) + 1;
        _diccionario.definir(x,cantidadIncrementada);
    }
}

template<class T>
int Multiconjunto<T>::ocurrencias(T x) const {
    if(!_diccionario.def(x)){
        return 0;
    }
    return _diccionario.obtener(x);
}
template<class T>
bool Multiconjunto<T>::operator<=(Multiconjunto<T> otro) const {
    std::vector<T> claves = _diccionario.claves();
    for (int i = 0; i < claves.size(); ++i) {
        if(ocurrencias(claves[i])<=otro.ocurrencias(claves[i])){
            // segui iterando
        }else{
            return false;
        }
    }
    return true;
}

