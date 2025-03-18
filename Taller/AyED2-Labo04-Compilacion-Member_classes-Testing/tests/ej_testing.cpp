#include "gtest-1.8.1/gtest.h"
#include "../src/Libreta.h"
#include "../src/Truco.h"
#include <map>
#include <cmath>

using namespace std;

// Ejercicio 4
TEST(Aritmetica, suma) {
    int s=15+7;
    EXPECT_EQ(s,22);
}

// Ejercicio 5
TEST(Aritmetica,Potencia) {
    float a=pow(10,2);
    EXPECT_EQ(a,100);
}

// Ejercicios 6..9

TEST(Aritmetica,potencia_general){

}

TEST(Diccionario,obtener){
    map<int,int> m;
    m[0]=1996;
    EXPECT_EQ(m[0],1996);
}

TEST(Diccionario,definir){
    map<int,int> m;
    EXPECT_EQ(0,m.count(0));
    m[0];
    EXPECT_EQ(1,m.count(0));
}

TEST(Truco,inicio){
    Truco truco;
    EXPECT_EQ(0,truco.puntaje_j1());
    EXPECT_EQ(0,truco.puntaje_j2());
}

TEST(Truco,buenas){
    Truco truco;
    EXPECT_EQ(false,truco.buenas(1));
    for (int i = 0; i < 16; ++i) {
        truco.sumar_punto(1);
    } // ahora puntaje_j1==15
    EXPECT_EQ(false,truco.buenas(1));
    truco.sumar_punto(1);
    EXPECT_EQ(true,truco.buenas(1));
    truco.sumar_punto(1);
    truco.sumar_punto(1);
    EXPECT_EQ(true,truco.buenas(1));
}