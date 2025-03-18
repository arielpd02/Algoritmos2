template <typename T>
string_map<T>::string_map():_size(0),raiz(nullptr){
    // COMPLETAR
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
void string_map<T>::copiarNodo(Nodo* nuevo,Nodo* copy){
        if(copy == nullptr){  //Si el nodo a copiar apunta a NULL , no hago nada mas (llegué a un end de la rama)
            return;
        }
        //Primero copio el significado si es que lo hay
        if(copy->definicion != nullptr) {
            nuevo->definicion = new T(*copy->definicion);
        }

        // Copio el array de nodos
        for (int i = 0; i < nuevo->siguientes.size(); ++i) {
            if(copy->siguientes[i] == nullptr){ //Si el nodo apunta a NULL
                //Continuo
            }else{
                nuevo->siguientes[i]= new Nodo();
                copiarNodo(nuevo->siguientes[i],copy->siguientes[i]);
                }
        }
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    if(d.raiz== nullptr){  //Caso trie vacío
        _size=0;
        raiz= nullptr;
    }else{                //Caso trie no vacio
        _size=d._size;
        raiz = new Nodo();
        for (int i = 0; i < raiz->siguientes.size(); ++i) {
            if(d.raiz->siguientes[i]== nullptr){
                //Continuo pues ya es NULL por el constructor de Nodo
            }else{
                raiz->siguientes[i] = new Nodo();
                copiarNodo(raiz->siguientes[i],d.raiz->siguientes[i]);
            }
        }
    }
    return *this;
    // COMPLETAR
}
template<typename T>
void string_map<T>::destruirNodos(Nodo* actual) {

    if(actual->definicion != nullptr){ //Si hay un espacio para el significado ,deletearlo
        delete actual->definicion;
    }
    vector<Nodo*> sig=actual->siguientes;
    for (int i = 0; i < sig.size(); ++i) {
        if(sig[i] != nullptr){
            destruirNodos(sig[i]);
        }else{
            //Nada , pues era NULL
        }
    }
    delete actual; //Borro el nodo
}

template <typename T>
string_map<T>::~string_map(){
    if(raiz == nullptr){
        //Nada
    }else{
        _size=0;
        for (int i = 0; i < raiz->siguientes.size(); ++i) {
            if(raiz->siguientes[i] != nullptr){
                destruirNodos(raiz->siguientes[i]);
            }else{
                //Nada , pues era NULL
            }
        }
        delete raiz;
    }
    // COMPLETAR
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& valor){
    string clave = valor.first;
    T significado =valor.second;

    if(empty()){ /* Caso trie vacio*/
        raiz = new Nodo();
        Nodo* actual=raiz;
        for(int i = 0; i < clave.size(); ++i) {
            int parte= int(clave[i]);

            Nodo* nuevo = new Nodo();
            actual->siguientes[parte]=nuevo;
            actual=nuevo;
        }
        T* def = new T(significado);  //Creo un espacio de memoria para guardar el significado (OJO CON DELETE!)
        actual->definicion = def;

    }else { /*Caso ya tenia elementos*/

        if (count(clave) == 1){ /*Si pertenece ,lo redefino*/
            Nodo* actual=raiz;
            for (int i = 0; i < clave.size(); ++i) {
                int parte =int(clave[i]);
                actual=actual->siguientes[parte];
                }
            *actual->definicion=significado;
        }else {
            Nodo *actual = raiz;
            for (int i = 0; i < clave.size(); ++i) {
                int parte = int(clave[i]);

                if (actual->siguientes[parte] != nullptr) {
                    actual = actual->siguientes[parte];
                } else {
                    Nodo *nuevo = new Nodo();
                    actual->siguientes[parte] = nuevo;
                    actual = nuevo;
                }
            }
            T *def = new T(significado);
            actual->definicion = def;
        }
    }
    /* Por último , aumento el size del árbol */
    _size++;
}




template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(empty()) {
        return 0;
    }else{
        Nodo* actual=raiz;
        for (int i = 0; i < clave.size(); ++i) {
            int parte =int(clave[i]);
            if(actual->siguientes[parte] == nullptr){
                return false;
            }else{
                actual=actual->siguientes[parte];
            }
        }
        if(actual->definicion!= nullptr){
            return 1;
        }else{
            return 0;
        }
    }
    // COMPLETAR
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int parte =int(clave[i]);
        actual= actual->siguientes[parte];
    }
    return *actual->definicion;
    // COMPLETAR
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo* actual=raiz;
    for (int i = 0; i < clave.size(); ++i) {
        int parte =int(clave[i]);
        actual= actual->siguientes[parte];
    }
    T sig= *actual->definicion;
    return *(actual->definicion);
    // COMPLETAR
}
template<typename T>
int string_map<T>::cantHijos(Nodo* actual){
    int hijos=0;
    for (int i = 0; i < actual->siguientes.size(); ++i) {
        if(actual->siguientes[i] != nullptr){
            hijos++;
        }
    }
    return hijos;
}
template<typename T>
bool string_map<T>::esNodoUtil(Nodo* actual){
    if(actual->definicion != nullptr){ //Si tiene significado
        return true;
    }else{
      if(cantHijos(actual)>1) //Si tiene más de un hijo
          return true;
    }
    return false;
}

template <typename T>
void string_map<T>::erase(const string &clave) {
    if(raiz == nullptr){ //Caso trie vacío
        return;
    }else{ //Caso trie no vacío
        Nodo* actual=raiz;
        Nodo* seed=actual;
        int iSeed=0;
        for (int i = 0; i < clave.size(); ++i) {
            int parte =int(clave[i]);
            if(esNodoUtil(actual)){
                seed=actual;
                iSeed=i; // Iseed es el índice del hijo de Seed siguiendo la clave
            }
            actual=actual->siguientes[parte];
        }
        //Encontre el nodo a borrar , borro su significado.
        delete actual->definicion;
        actual->definicion= nullptr;
        _size--;

        if(cantHijos(actual)>0){ //Si el nodo a borrar tiene hijos, finaliza ya que es nodo útil
            return;
        }else{                   //Si no tenía hijos , debo borrar los descendientes de seed
            Nodo* siguiente = seed->siguientes[clave[iSeed]];
            seed->siguientes[clave[iSeed]]= nullptr;
            seed=siguiente;
            iSeed++;
            for(int i = iSeed; i < clave.size(); ++i) {
                int parte =int(clave[i]);
                siguiente=seed->siguientes[parte];
                delete seed;
                seed=siguiente;
            }
            delete seed;
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
    // COMPLETAR
}

template <typename T>
bool string_map<T>::empty() const{
    return (_size==0);
    // COMPLETAR
}