#ifndef _COLAPRIOR_H_
#define _COLAPRIOR_H_

#include <map>
#include <string>

using namespace std;

template<class T>
class ColaPrior {
public:
	ColaPrior(bool m = false);
    ~ColaPrior();

	void encolar(const T& elem);
	void desencolar();
    void borrar(const T& elem);
    bool pertenece(const T& elem) const;
    const T& proximo() const;
    int tam();

private:
    struct Nodo {
        Nodo(T* val): izq(nullptr), der(nullptr), padre(nullptr), val(val) {}
        Nodo* izq;
        Nodo* der;
        Nodo* padre;
        typename map<T, pair<Nodo*, int>>::iterator it;
        T* val;
    };

    Nodo* raiz;
    int ultimo;
    int size;
    bool min;
    map<T, pair<Nodo*, int>> mapping;

    void destruir(Nodo* n);
    void swap(Nodo* padre, Nodo* hijo);
    void sift_up(Nodo* n);
    void sift_down();
    void insertar(Nodo* n);
    bool cmp(const T& a, const T& b) const;
    Nodo* buscar(Nodo* n, int camino);
};

#include "ColaPrior.hpp"

#endif /*_COLAPRIOR_H_*/
