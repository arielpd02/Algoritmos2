#include <iostream>
#include <vector>
#include <algorithm>
#include "gtest-1.8.1/gtest.h"

#include "../src/ColaPrior.h"
#include "../src/Gasto.h"

using namespace std;

TEST(ColaPrior, vacio) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, encolarUno) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(10);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 10);
}

TEST(ColaPrior, encolarMenor) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(3);
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(4);
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 5);
}

TEST(ColaPrior, encolarMenorMin) {
    ColaPrior<int> q(true);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(3);
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 3);
    q.encolar(4);
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 3);
}

TEST(ColaPrior, encolarMayor) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(6);
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 6);
    q.encolar(7);
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 7);
}

TEST(ColaPrior, encolarMayorMin) {
    ColaPrior<int> q(true);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(6);
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 5);
    q.encolar(7);
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 5);
}

TEST(ColaPrior, desencolarMismo) {
    ColaPrior<int> q(false);
    q.encolar(5);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, desencolarMismoMin) {
    ColaPrior<int> q(true);
    q.encolar(5);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, desencolarMenor) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(51);
    q.encolar(42);
    q.encolar(33);
    q.encolar(24);
    q.encolar(15);
    ASSERT_EQ(q.proximo(), 51);
    ASSERT_EQ(q.tam(), 5);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 42);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 33);
    ASSERT_EQ(q.tam(), 3);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 24);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 15);
    ASSERT_EQ(q.tam(), 1);
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, borrar) {
    ColaPrior<int> q;
    q.encolar(1);
    q.encolar(2);
    q.encolar(3);
    q.encolar(4);
    q.encolar(4);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 6);
    ASSERT_EQ(q.proximo(), 5);
    q.borrar(4);
    ASSERT_EQ(q.tam(), 5);
    q.borrar(4);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 3);
}

TEST(ColaPrior, borrarMin) {
    ColaPrior<int> q(true);
    q.encolar(1);
    q.encolar(2);
    q.encolar(3);
    q.encolar(4);
    q.encolar(4);
    q.encolar(5);
    ASSERT_EQ(q.tam(), 6);
    ASSERT_EQ(q.proximo(), 1);
    q.borrar(4);
    ASSERT_EQ(q.tam(), 5);
    q.borrar(4);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), 2);
    q.desencolar();
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 3);
    q.desencolar();
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 5);
}

TEST(ColaPrior, borrarRaiz) {
    ColaPrior<int> q;
    q.encolar(1);
    q.encolar(1);
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), 1);
    q.borrar(1);
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), 1);
    q.borrar(1);
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, borrarMenor) {
    ColaPrior<int> q;
    ASSERT_EQ(q.tam(), 0);
    q.encolar(51);
    q.encolar(42);
    q.encolar(33);
    q.encolar(24);
    q.encolar(15);
    ASSERT_EQ(q.proximo(), 51);
    ASSERT_EQ(q.tam(), 5);
    q.borrar(51);
    ASSERT_FALSE(q.pertenece(51));
    ASSERT_EQ(q.proximo(), 42);
    ASSERT_EQ(q.tam(), 4);
    q.borrar(42);
    ASSERT_FALSE(q.pertenece(42));
    ASSERT_EQ(q.proximo(), 33);
    ASSERT_EQ(q.tam(), 3);
    q.borrar(33);
    ASSERT_FALSE(q.pertenece(33));
    ASSERT_EQ(q.proximo(), 24);
    ASSERT_EQ(q.tam(), 2);
    q.borrar(24);
    ASSERT_FALSE(q.pertenece(24));
    ASSERT_EQ(q.proximo(), 15);
    ASSERT_EQ(q.tam(), 1);
    q.borrar(15);
    ASSERT_EQ(q.tam(), 0);
    ASSERT_FALSE(q.pertenece(15));
}

TEST(ColaPrior, desencolarMenorMin) {
    ColaPrior<int> q(true);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(51);
    q.encolar(42);
    q.encolar(33);
    q.encolar(24);
    q.encolar(15);
    ASSERT_EQ(q.proximo(), 15);
    ASSERT_EQ(q.tam(), 5);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 24);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 33);
    ASSERT_EQ(q.tam(), 3);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 42);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 51);
    ASSERT_EQ(q.tam(), 1);
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, desencolarMayor) {
    ColaPrior<int> q(false);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(15);
    q.encolar(24);
    q.encolar(33);
    q.encolar(42);
    q.encolar(51);
    ASSERT_EQ(q.proximo(), 51);
    ASSERT_EQ(q.tam(), 5);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 42);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 33);
    ASSERT_EQ(q.tam(), 3);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 24);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 15);
    ASSERT_EQ(q.tam(), 1);
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, desencolarMayorMin) {
    ColaPrior<int> q(true);
    ASSERT_EQ(q.tam(), 0);
    q.encolar(15);
    q.encolar(24);
    q.encolar(33);
    q.encolar(42);
    q.encolar(51);
    ASSERT_EQ(q.proximo(), 15);
    ASSERT_EQ(q.tam(), 5);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 24);
    ASSERT_EQ(q.tam(), 4);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 33);
    ASSERT_EQ(q.tam(), 3);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 42);
    ASSERT_EQ(q.tam(), 2);
    q.desencolar();
    ASSERT_EQ(q.proximo(), 51);
    ASSERT_EQ(q.tam(), 1);
    q.desencolar();
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, gastoPersona) {

    ColaPrior<Gasto> q(false);

    Gasto gp1(10, 1);
    Gasto gp2(10, 2);
    Gasto gp3(20, 4);
    Gasto gp4(20, 3);
    q.encolar(gp1);
    q.encolar(gp2);
    q.encolar(gp3);
    q.encolar(gp3);
    q.encolar(gp4);

    ASSERT_EQ(q.tam(), 5);
    ASSERT_EQ(q.proximo(), gp4);
    q.desencolar();
    ASSERT_EQ(q.tam(), 4);
    ASSERT_EQ(q.proximo(), gp3);
    q.desencolar();
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), gp3);
    q.desencolar();
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), gp1);
}

TEST(ColaPrior, gastoPersonaBorrar) {

    ColaPrior<Gasto> q(false);

    Gasto gp1(10, 1);
    Gasto gp2(10, 2);
    Gasto gp3(20, 4);
    Gasto gp4(20, 3);
    q.encolar(gp1);
    q.encolar(gp2);
    q.encolar(gp3);
    q.encolar(gp3);
    q.encolar(gp4);

    ASSERT_EQ(q.tam(), 5);
    ASSERT_EQ(q.proximo(), gp4);
    q.borrar(gp3);
    ASSERT_TRUE(q.pertenece(gp3));
    ASSERT_EQ(q.tam(), 4);
    ASSERT_EQ(q.proximo(), gp4);
    q.borrar(gp3);
    ASSERT_FALSE(q.pertenece(gp3));
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), gp4);
    q.borrar(gp2);
    ASSERT_FALSE(q.pertenece(gp2));
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), gp4);
    q.borrar(gp1);
    ASSERT_FALSE(q.pertenece(gp1));
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), gp4);
    q.desencolar();
    ASSERT_FALSE(q.pertenece(gp4));
    ASSERT_EQ(q.tam(), 0);
}

TEST(ColaPrior, gastoPersonaMin) {

    ColaPrior<Gasto> q(true);

    Gasto gp1(10, 1);
    Gasto gp2(10, 2);
    Gasto gp3(20, 4);
    Gasto gp4(20, 3);
    q.encolar(gp1);
    q.encolar(gp2);
    q.encolar(gp3);
    q.encolar(gp3);
    q.encolar(gp4);

    ASSERT_EQ(q.tam(), 5);
    ASSERT_EQ(q.proximo(), gp2);
    q.desencolar();
    ASSERT_FALSE(q.pertenece(gp2));
    ASSERT_EQ(q.tam(), 4);
    ASSERT_EQ(q.proximo(), gp1);
    q.desencolar();
    ASSERT_FALSE(q.pertenece(gp1));
    ASSERT_EQ(q.tam(), 3);
    ASSERT_EQ(q.proximo(), gp3);
    q.desencolar();
    ASSERT_TRUE(q.pertenece(gp3));
    ASSERT_EQ(q.tam(), 2);
    ASSERT_EQ(q.proximo(), gp3);
    q.desencolar();
    ASSERT_FALSE(q.pertenece(gp3));
    ASSERT_EQ(q.tam(), 1);
    ASSERT_EQ(q.proximo(), gp4);
}

TEST(ColaPrior, por_copia) {
    ColaPrior<Gasto> q(false);

    Gasto gp1(10, 1);
    Gasto gp2(10, 2);
    Gasto gp3(20, 4);
    Gasto gp4(20, 3);
    q.encolar(gp1);
    q.encolar(gp2);
    q.encolar(gp3);
    q.encolar(gp3);
    q.encolar(gp4);

    ASSERT_EQ(q.tam(), 5);
    ASSERT_EQ(q.proximo(), gp4);

    ColaPrior<Gasto> copia(q);

    ASSERT_EQ(copia.tam(), 5);
    ASSERT_EQ(copia.proximo(), gp4);

    copia.desencolar();
    copia.desencolar();
    copia.desencolar();
    copia.desencolar();
    copia.desencolar();

    ASSERT_EQ(copia.tam(), 0);
    ASSERT_EQ(q.tam(), 5);
}