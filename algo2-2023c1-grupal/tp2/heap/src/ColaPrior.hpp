
#include "ColaPrior.h"

template<class T>
ColaPrior<T>::ColaPrior(bool m) {
	raiz = nullptr;
    ultimo = 0;
    size = 0;
    min = m;
}

template<class T>
ColaPrior<T>::~ColaPrior() {
    destruir(raiz);
}

template<class T>
void ColaPrior<T>::destruir(typename ColaPrior<T>::Nodo* n) {
    if (n != nullptr) {
        destruir(n->izq);
        destruir(n->der);
        delete n->val;
        delete n;
    }
}

template<class T>
int ColaPrior<T>::tam() {
    return size;
}

template<class T>
void ColaPrior<T>::encolar(const T& val) {
    if (mapping.count(val) > 0) {
        mapping[val].second++;
    } else {
        T* copy = new T(val);
        Nodo* nuevo = new Nodo(copy);
        mapping[val] = {nuevo, 1};
        nuevo->it = mapping.find(val);  // O(log(U))
        insertar(nuevo);
        sift_up(nuevo);
    }
    size++;
}

template<class T>
const T& ColaPrior<T>::proximo() const {
	return *(raiz->val);
}

template<class T>
void ColaPrior<T>::borrar(const T& val) {
    if (mapping[val].second > 1) {
        mapping[val].second--;
        size--;
        return;
    }
    Nodo* n = mapping[val].first;

    // Lo mandamos a la raíz y desencolamos
    while (n->padre != nullptr) {
        swap(n->padre, n);
        n = n->padre;
    }
    desencolar();
}

template<class T>
void ColaPrior<T>::desencolar() {
    if (mapping[proximo()].second > 1) {
        mapping[proximo()].second--;
        size--;
        return;
    }
    Nodo* ult = buscar(raiz, ultimo);

    if (raiz == ult) {
        mapping.erase(raiz->it);
        delete raiz->val;
        delete raiz;
        raiz = nullptr;
    } else {
        swap(raiz, ult);

        if (ult->padre->izq == ult) {
            ult->padre->izq = nullptr;
        } else {
            ult->padre->der = nullptr;
        }
        mapping.erase(ult->it);
        delete ult->val;
        delete ult;
        ult = nullptr;

        sift_down();
    }

    // Restamos 1 al tamaño
    ultimo--;
    size--;
}

template<class T>
void ColaPrior<T>::insertar(ColaPrior::Nodo* n) {
    ultimo = ultimo + 1;

    // Nos fijamos si vamos a insertar la raíz
    if (ultimo == 1) {
        raiz = n;
        return;
    }

    // Si no es raíz, buscamos al padre recorriendo el camino
    // desde la raíz hasta la posición en la que iría el nodo,
    // no incluyendo ninguna de las dos.
    Nodo* padre = buscar(raiz, ultimo);
    n->padre = padre;

    // Insertamos al hijo en la posición que corresponda del padre
    if (padre->izq == nullptr) {
        padre->izq = n;
    } else {
        padre->der = n;
    }
}

template<class T>
typename ColaPrior<T>::Nodo* ColaPrior<T>::buscar(ColaPrior<T>::Nodo *n, int camino) {
    if (camino <= 1) {
        return n;
    }
    Nodo* prox = buscar(n, camino / 2);
    if (camino % 2 == 1) {
        if (prox->der != nullptr) {
            return prox->der;
        }
        return prox;
    }
    if (prox->izq != nullptr) {
        return prox->izq;
    }
    return prox;
}

template<class T>
void ColaPrior<T>::sift_up(ColaPrior<T>::Nodo* n) {
    Nodo* actual = n;
    while (actual->padre != nullptr && cmp(*(actual->val), *(actual->padre->val))) {
        swap(actual->padre, actual);
        actual = actual->padre;
    }
}

template<class T>
void ColaPrior<T>::sift_down() {
    // Hacemos sift down de la raíz
    Nodo* actual = raiz;
    while (actual->izq != nullptr || actual->der != nullptr) {
        Nodo* mayor = actual->izq;

        if (actual->der != nullptr && cmp(*(actual->der->val), *(actual->izq->val))) {
            mayor = actual->der;
        }

        if (cmp(*(mayor->val), *(actual->val))) {
            swap(actual, mayor);
            actual = mayor;
        } else {
            break;
        }
    }
}

template<class T>
void ColaPrior<T>::swap(ColaPrior::Nodo* padre, ColaPrior::Nodo* hijo) {
    // Nos guardamos temporalmente el mapping, el valor y el iterador
    // del padre
    auto node_tmp = padre->it->second.first;
    auto it_tmp = padre->it;
    T* val_tmp = padre->val;

    // Actualizamos el nodo del mapping
    padre->it->second.first = hijo->it->second.first;
    hijo->it->second.first = node_tmp;

    // Swap valores
    padre->val = hijo->val;
    hijo->val = val_tmp;

    // Swap iteradores
    padre->it = hijo->it;
    hijo->it = it_tmp;
}

template<class T>
bool ColaPrior<T>::cmp(const T& a, const T& b) const {
    if (min) {
        return a < b;
    }
    return a > b;
}

template<class T>
bool ColaPrior<T>::pertenece(const T& elem) const {
    return mapping.count(elem) > 0;
}
