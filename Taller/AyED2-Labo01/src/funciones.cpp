#include <vector>
#include "algobot.h"

using namespace std;

// Ejercicio 1
bool pertenece(vector<int> w,int n){
    bool res=false;
    for(int i=0;i<w.size();i++) {
        if (w[i] == n) {
            res=true;
        }
    }
    return res ;
}

vector<int> quitar_repetidos(vector<int> s) {
    vector<int> w;
    for(int i=0;i<s.size();i++){
        if(pertenece(w,s[i])){
            //No hagas nada
        }else{
            w.push_back(s[i]);
        }
    }
    return w;
}

// Ejercicio 2
vector<int> quitar_repetidos_v2(vector<int> s) {
    set<int> A;
    vector<int> res;
    for(int i=0;i<s.size();i++){
        if(A.count(s[i])==0){
            res.push_back(s[i]);
            A.insert(s[i]);
        }else{
           //Nada
        }
    }
    return res;
}

// Ejercicio 3
bool mismos_elementos(vector<int> a, vector<int> b) {
    return true;
}

// Ejercicio 4
bool mismos_elementos_v2(vector<int> a, vector<int> b) {
    set<int> set_a;
    set<int> set_b;
    for(int n : a){
        set_a.insert(n);
    }
    for (int m: b) {
        set_b.insert(m);
    }
    return (set_a==set_b);
}

// Ejercicio 5
int cantApariciones(vector<int> s,int n){
    int res=0;
    for (int i = 0; i < s.size(); ++i) {
        if(s[i]==n) ++res;
    }
    return res;
}

map<int, int> contar_apariciones(vector<int> s) {
    map<int,int> m;
    for (int i = 0; i < s.size(); ++i) {
        if(m.count(s[i])==1){

        } else {
            m[s[i]]= cantApariciones(s,s[i]);
        }
    }
    return m ;
}

// Ejercicio 6
vector<int> filtrar_repetidos(vector<int> s) {  // Asi es O(n^2)
    vector<int> res;
    for (int i = 0; i < s.size(); ++i) {
        if(cantApariciones(s,s[i])==1){
            res.push_back(s[i]);
        }
    }
    return res;
}

// Ejercicio 7

set<int> interseccion(set<int> a, set<int> b) {
    set<int> inter;
    for (int i:a) {
        if(b.count(i)==1){
            inter.insert(i);
        }
    }
 return inter;
}

// Ejercicio 8
map<int, set<int>> agrupar_por_unidades(vector<int> s) {
    map<int,set<int>> m;
    for (int i = 0; i < s.size(); ++i) {
            m[s[i] % 10 ].insert(s[i]);
        }
    return m;
}

// Ejercicio 9

char devuelveTraduccion(vector<pair<char,char>> tr ,char c){
    char k;
    for (int i = 0; i < tr.size(); ++i) {
        pair<char,char> tupla=tr[i];
        if(tupla.first==c){
            k= tupla.second;
            break;
        }
    }
    return k;
}
vector<char> traducir(vector<pair<char, char>> tr, vector<char> str) {
    vector<char> res(str.size());
    set<char> claves;
    for (int i = 0; i < tr.size(); ++i) {
        claves.insert(tr[i].first);
    }
    for (int j = 0; j < str.size(); ++j) {
        if (claves.count(str[j]) == 1){
            res[j]= devuelveTraduccion(tr,str[j]);
        }else{
            res[j]=str[j];
        }
    }
    return res;
}

// Ejercicio 10

bool integrantes_repetidos(vector<Mail> s) {
    bool res= false;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < s.size() && j!=i ; ++j) {
            for (LU lu : s[i].libretas()) {
                if(s[j].libretas().count(lu) == 1){

                    res =  (s[i].asunto()!=s[j].asunto()); // Si son distintos , es verdadero que hay int. repetidos

                }
            }
        }
    }
    return res;
}

// Ejercicio 11

Mail ultimoMailAdjunto(vector<Mail> s,string asunto){
    Mail m;
    Fecha ultFecha = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i].asunto() == asunto){
            if(s[i].fecha()>ultFecha){
                if( s[i].adjunto()) {
                    m = s[i];
                    ultFecha = s[i].fecha();
                }
            } else{
                ultFecha=s[i].fecha();
            }
        }
    }
    return m;
}

map<set<LU>, Mail> entregas_finales(vector<Mail> s) {
    map<set<LU>,Mail> dicc;
    for (int i = 0; i < s.size(); ++i) {
        if(s[i]== ultimoMailAdjunto(s,s[i].asunto())){
            dicc[s[i].libretas()]= s[i];
        }
    }
  return dicc;
}



