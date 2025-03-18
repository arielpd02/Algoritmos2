#ifndef ALGO2_LABO_CLASE5_ALGORITMOS_H
#define ALGO2_LABO_CLASE5_ALGORITMOS_H

#include <utility>
#include <iterator>
#include <vector>

// Completar con las funciones del enunciado

template<class Contenedor> //Modifico ejer. no usando asignacion sobre value_type
typename Contenedor::value_type minimo(const Contenedor& c){
    typename Contenedor::const_iterator it = c.begin();
    typename Contenedor::const_iterator min = c.begin();
    for (typename Contenedor::const_iterator iter = it; iter!=c.end(); ++iter) {
        if(*iter<=*min)
            min=iter;
    }
    return *min;
}

template<class Contenedor>
typename Contenedor::value_type promedio(const Contenedor& c){
    typename Contenedor::value_type sumatoria = 0;
    int tam = 0; //Por Pre , ¬vacio(c) , luego nunca divido por 0
    for (typename Contenedor::const_iterator it = c.begin();it!=c.end();it++){
            sumatoria+=*it;
            tam++;
    }
    return (sumatoria/tam);
}


template<class Iterator>
typename Iterator::value_type minimoIter(const Iterator& desde,const Iterator& hasta){
    Iterator min=desde;
    for (Iterator iter=desde;iter!=hasta;iter++){
        if(*iter<=*min)
            min=iter;
    }
    return *min;
}
template<class Iterator>
typename Iterator::value_type promedioIter(const Iterator& desde, const Iterator& hasta){
    typename Iterator::value_type sumatoria = 0;
    typename Iterator::value_type tam = 0;
    for (Iterator iter=desde; iter!=hasta ; iter++) {
        sumatoria+=*iter;
        tam++;
    }
    return (sumatoria/tam);
}






template<class Contenedor>
void filtrar(Contenedor &c, const typename Contenedor::value_type& elem){
    for (typename Contenedor::iterator it = c.begin();it != c.end();it++){
        if(*it == elem) {
            it = c.erase(it);
            if(it != c.begin()){ //Si no estoy en el primer elemento
                it--;
            }else{               //Caso contrario , llevalo al inicio
                it=c.begin();
            }
        }
    }
}

template<class Contenedor>
bool ordenado(const Contenedor& c){
    typename Contenedor::const_iterator iter = c.begin();

    while(iter!=c.end()){
        auto prox = iter;
        prox++;
        if(prox==c.end())
            break;
        if(*iter >= *prox){
            return false;
        }
        iter++;
    }

    return true;
}

template<class Contenedor>
std::pair<Contenedor, Contenedor> split(const Contenedor & c , const typename Contenedor::value_type& elem){
    Contenedor c1;
    Contenedor c2;
    typename Contenedor::const_iterator iter = c.begin();
    typename Contenedor::iterator iter1=c1.begin();
    typename Contenedor::iterator iter2=c2.begin();
    while(iter!=c.end()){
        if(*iter<elem){
            iter1=c1.insert(iter1,*iter);
            iter1++;                    //Me muevo para el sig.elemento (notar que el retroceso no vale)
        }else{
            iter2=c2.insert(iter2,*iter);
            iter2++;                    //Me muevo para el sig.elemento (notar que el retroceso no vale)
        }
        iter++;
    }
    return std::make_pair(c1,c2);
}

template<class Contenedor>
void merge(const Contenedor& c1,const Contenedor& c2,Contenedor& res){
    typename Contenedor::const_iterator it1=c1.begin();
    typename Contenedor::const_iterator it2=c2.begin();
    typename Contenedor::const_iterator itR=res.begin();
    while ( (it1!=c1.end()) && (it2!=c2.end()) ){
        if(*it1<=*it2){
            itR=res.insert(itR,*it1);
            itR++;
            it1++;
        }else{
            itR=res.insert(itR,*it2);
            itR++;
            it2++;
        }
    }

    if(it1==c1.end()){
        while(it2!=c2.end()){
            itR=res.insert(itR,*it2);
            itR++;
            it2++;
        }
    }else{  //En este caso , ya recorri c2 y me podria faltar terminar c1
        while (it1!=c1.end()){
            itR=res.insert(itR,*it1);
            itR++;
            it1++;
        }
    }
}



#endif //ALGO2_LABO_CLASE5_ALGORITMOS_H
