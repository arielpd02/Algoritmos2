#include <iostream>
#include "list"

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    void incrementar_dia();
    // Completar declaraciones funciones
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    int _mes;
    int _dia;
    //Completar miembros internos
};

Fecha::Fecha(int mes, int dia): _mes(mes),_dia(dia){};
int Fecha::mes() {
    return _mes;
}
int Fecha::dia() {
    return _dia;
}
ostream& operator<<(ostream& os,Fecha f){
    os<<f.dia()<<"/"<<f.mes();
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia() and this-> mes() == o.mes();
    // Completar iguadad (ej 9)
    return igual_dia;
}
#endif
void Fecha::incrementar_dia() {
    if(_mes==12){
        if(_dia == dias_en_mes(11)){ //Happy New Year :)
            _mes=1;
            _dia=1;
        }else{
            _dia++;
        }
    }else{
        if(_dia == dias_en_mes(_mes)){
            _mes++;
            _dia=1;
        }else{
            _dia++;
        }
    }
}

// Ejercicio 11, 12

// Clase Horario Pre: 0<=hora<23 && 0<=min<60
class Horario{
public:
    Horario(uint hora,uint min);
    uint hora();
    uint min();
    bool operator==(Horario otro);
    bool operator<(Horario otro);
private:
    uint _hora;
    uint _min;
};

Horario::Horario(uint hora, uint min): _hora(hora),_min(min) {};
uint Horario::hora() {
    return _hora;
}
uint Horario::min() {
    return _min;
}
ostream& operator<<(ostream& os , Horario h){
    os<<h.hora()<<":"<<h.min();
    return os;
}
bool Horario::operator==(Horario otro) {
    bool mismohorario = hora()==otro.hora() and min()==otro.min();
    return mismohorario;
}

bool Horario::operator<(Horario otro) {
    if(hora()==otro.hora()){
        return (min()<otro.min());
    }else{
        return (hora()<otro.hora());
    }
}



// Ejercicio 13

// Clase Recordatorio

class Recordatorio{
public:
    Recordatorio(Fecha f, Horario h, string m);
    Fecha fecha();
    Horario horario();
    string mensaje();
private:
    Fecha _fecha;
    Horario _horario;
    string _mensaje;
};

Recordatorio:: Recordatorio(Fecha f, Horario h,string m): _fecha(f), _horario(h),_mensaje(m){};
Fecha Recordatorio::fecha() {
    return _fecha;
}
Horario Recordatorio::horario() {
    return _horario;
}
string Recordatorio::mensaje() {
    return _mensaje;
}

ostream& operator<<(ostream& os,Recordatorio r){
    os<<r.mensaje()<<" "<<"@ "<<r.fecha()<<" "<<r.horario();
    return os;
}


// Ejercicio 14

// Clase Agenda

class Agenda{
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();
private:
    Fecha _fechaActual;
    vector<vector<list<Recordatorio>>> _recordatorios;
};

Agenda::Agenda(Fecha fecha_inicial): _fechaActual(fecha_inicial.mes(),fecha_inicial.dia()),
_recordatorios(12,vector<list<Recordatorio>>(31)) {};

void Agenda::agregar_recordatorio(Recordatorio rec) {
    _recordatorios[rec.fecha().mes()][rec.fecha().dia()].push_back(rec);
}

void Agenda::incrementar_dia() {
    return _fechaActual.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    return _recordatorios[_fechaActual.mes()][_fechaActual.dia()];
}

Fecha Agenda::hoy() {
    return _fechaActual;
}


list<Recordatorio> ordenarLista(list<Recordatorio> lista){
    vector<Recordatorio> aux;
    for (Recordatorio r: lista) {
        aux.push_back(r);
    } //Ordeno la sec de recordatorios segun los horarios ascendentemente
    for (int i = 0; i < aux.size(); ++i) {
        for (int j = 0; j < aux.size(); ++j) {
            if (aux[i].horario()<aux[j].horario())
                swap(aux[i],aux[j]);
        }
    }
     //Vacio la lista
    lista.clear();
    //Le inserto los elementos a la lista respetando el orden
    for (int i = 0; i < aux.size(); ++i) {
        lista.push_back(aux[i]);
    }
    return lista;
}


ostream& operator<<(ostream& os,Agenda a){
    os<<a.hoy()<<endl;
    os<<"====="<<endl;
    list<Recordatorio> l = a.recordatorios_de_hoy();
    l= ordenarLista(l);
    for (Recordatorio r: l) {
        os<<r<<endl;
    }
    return os;
}


