//Ej1
template<class T>
T cuadrado(T x){
    return x*x;
}
//EJ2
template<class Contenedor,class Elem>
bool contiene(Contenedor c,Elem e){
    for (int i = 0; i < c.size(); ++i) {
        if(c[i]==e)
            return true;
    }
    return false;
}
//EJ3
template<class Contenedor>
bool esPrefijo(Contenedor a,Contenedor b){
    if(a.size()<=b.size()){
        for (int i = 0; i < a.size(); ++i) {
            if(a[i]!=b[i])
                return false;
        }
    }else{
        return false;
    }
    return true;
}
//Ej4

template<class Contenedor,class Elem>
Elem maximo(Contenedor c){
    Elem maximo=c[0];
    if(c.size()==1){
        return c[0];
    }else{
        for (int i = 0; i < c.size(); ++i) {
            if(c[i]>=maximo)
                maximo=c[i];
        }
    }
    return maximo;
}






