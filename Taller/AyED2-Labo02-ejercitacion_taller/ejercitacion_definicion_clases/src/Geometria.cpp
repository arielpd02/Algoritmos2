#include <iostream>

using namespace std;

using uint = unsigned int;

// Ejercicio 1

class Rectangulo {
    public:
        Rectangulo(uint alto, uint ancho);
        uint alto();
        uint ancho();
        float area();

    private:
        int alto_;
        int ancho_;

};

Rectangulo::Rectangulo(uint alto, uint ancho) : alto_(alto),ancho_(ancho) {};

uint Rectangulo::alto() {
    return alto_;
    // Completar
}

// Completar definición: ancho
uint Rectangulo::ancho() {
    return ancho_;
}

// Completar definición: area
float Rectangulo::area(){
    return (alto_ * ancho_);
}

// Ejercicio 2

// Clase Elipse
float PI=3.14;
class Elipse{
    public:
        Elipse(uint a,uint b);
        uint r_a();
        uint r_b();
        float area();
    private:
    uint _r_a;
    uint _r_b;
};

Elipse::Elipse(uint a, uint b):_r_a(a),_r_b(b){};

uint Elipse::r_a() {
    return _r_a;
}
uint Elipse::r_b(){
    return _r_b;
};
float Elipse::area() {
    return (_r_a * _r_b * PI);
}


// Ejercicio 3

class Cuadrado {
    public:
        Cuadrado(uint lado);
        uint lado();
        float area();

    private:
        Rectangulo r_;
};

Cuadrado::Cuadrado(uint lado): r_(lado, lado) {};

uint Cuadrado::lado() {
    return r_.ancho();
    // Completar
}

float Cuadrado::area() {
    return r_.area();
    // Completar
}

// Ejercicio 4

// Clase Circulo
class Circulo{
public:
    Circulo(uint radio);
    uint radio();
    float area();
private:
    Elipse _c;
};

Circulo::Circulo(uint radio): _c(radio,radio) {};
uint Circulo::radio() {
    return _c.r_a();
}
float Circulo::area() {
    return _c.area();
}
// Ejercicio 5

ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.ancho() << ", " << r.alto() << ")";
    return os;
}

// ostream Elipse
ostream& operator<<(ostream& os, Elipse e){
    os<< "Elipse("<<e.r_a()<<","<<e.r_b()<<")";
    return os;
}

// Ejercicio 6'

ostream& operator<<(ostream& os,Cuadrado c){
    os<<"Cuad("<<c.lado()<<")";
    return os;
}
ostream& operator<<(ostream& os , Circulo c){
    os<<"Circ("<<c.radio()<<")";
    return os;
}


