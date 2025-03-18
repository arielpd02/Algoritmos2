#include "string"
#include "vector"

template<class Clave,class Valor>
class Diccionario{
public:
    Diccionario();
    void definir(Clave k ,Valor v);
    bool def(Clave k) const;
    Valor obtener(Clave k) const;
    std::vector<Clave> claves() const;
private:
    struct Asociacion{
        Asociacion(Clave k,Valor v);
        Clave _clave;
        Valor _valor;
    };
    std::vector<Asociacion> _asociaciones;
};

template<class Clave,class Valor>
Diccionario<Clave,Valor>::Diccionario() {}

template<class Clave,class Valor>
Diccionario<Clave,Valor>::Asociacion::Asociacion(Clave k, Valor v): _clave(k),_valor(v) {}

template<class Clave,class Valor>
void Diccionario<Clave,Valor>::definir(Clave k, Valor v) {
    for (unsigned int i = 0; i < _asociaciones.size(); ++i) {
        if(_asociaciones[i]._clave == k){
            _asociaciones[i]._valor=v;
        }
    }
    _asociaciones.push_back(Asociacion(k,v));
}
template<class Clave,class Valor>
bool Diccionario<Clave,Valor>::def(Clave k) const {
    for ( unsigned int i = 0; i < _asociaciones.size(); ++i) {
        if(_asociaciones[i]._clave == k)
            return true;
    }
    return  false;
}
template<class Clave,class Valor>
Valor Diccionario<Clave,Valor>::obtener(Clave k) const {
    for (int i = 0; i < _asociaciones.size(); ++i) {
        if(_asociaciones[i]._clave == k)
            return _asociaciones[i]._valor;
    }
}

//----------------------------------Implementacion de Selection Sort--------------------------------------------
template<class Clave>
void swap(std::vector<Clave> &arr, int &a,int &b){    //Funciona!!
    if(a==b) //Si es el mismo elemento pues mismo indice, no lo intercambies
        return;
    // { a=a_0 ^ b=b_0 }
    arr[a]=arr[a]+arr[b];
    // {a=a_0+b_0 ^ b=b_0}
    arr[b]=arr[a]-arr[b];
    // {a=a_0+b_0 ^ b=a_0}
    arr[a]=arr[a]-arr[b];
    // {a=b_0 ^ b=a_0}
}

template<class Clave>
int indiceMinElem(std::vector<Clave> &v,int desde ,int hasta){
    int min = desde;
    for (int i = desde+1; i <hasta ; ++i) {
        if(v[i]<v[min]){
            min=i;
        }
    }
    return min;
}

template<class Clave>
void selectionSort(std::vector<Clave> &arr){
    for (int i = 0; i < arr.size()- 1; ++i) {
        int indMinimoSubsec= indiceMinElem(arr,i,arr.size());
        swap(arr,i, indMinimoSubsec);
    }
}
//------------------------------------------------------------------------------------------------------------

// Implementacion de claves

template<class Clave,class Valor>
std::vector<Clave> Diccionario<Clave,Valor>::claves()const {
    std::vector<Clave> v; //Si es un dicc vacio => devolve vector vacio
    if(_asociaciones.empty()){
        return v;
    }
    for (int i = 0; i < _asociaciones.size(); ++i) {
        v.push_back(_asociaciones[i]._clave);
    }
    //Ahora ordeno el vector de claves
    selectionSort(v);
    return v;
}

