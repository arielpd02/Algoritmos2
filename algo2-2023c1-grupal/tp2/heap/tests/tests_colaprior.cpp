#include <iostream>
#include <vector>
#include <algorithm>
#include "gtest-1.8.1/gtest.h"

#include "../src/ColaPrior.h"

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

struct Log {
    Log(int g, int p): gasto(g), per(p) {}
    int gasto;
    int per;

    bool operator<(const Log& l) const {
        if (gasto != l.gasto) {
            return gasto < l.gasto;
        }
        return per > l.per;
    }
    bool operator>(const Log& l) const {
        return !(*this == l) && !(*this < l);
    }

    bool operator<=(const Log& l) const {
        return (l < *this) || (l == *this);
    }

    bool operator>=(const Log& l) const {
        return !(*this < l);
    }

    bool operator==(const Log& l) const {
        return gasto == l.gasto && per == l.per;
    }

    bool operator!=(const Log& l) const {
        return !(*this == l);
    }
};

TEST(ColaPrior, gastoPersona) {

    ColaPrior<Log> q(false);

    Log gp1(10, 1);
    Log gp2(10, 2);
    Log gp3(20, 4);
    Log gp4(20, 3);
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

    ColaPrior<Log> q(false);

    Log gp1(10, 1);
    Log gp2(10, 2);
    Log gp3(20, 4);
    Log gp4(20, 3);
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

    ColaPrior<Log> q(true);

    Log gp1(10, 1);
    Log gp2(10, 2);
    Log gp3(20, 4);
    Log gp4(20, 3);
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

void mostrar(vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

void siguiente_permutacion(vector<int>& vec, int i) {
    int p = 1;
    while (i > 0 && i % (p + 1) == 0) {
        p++;
        i /= p;
    }
    swap(vec[0], vec[p]);
}

const int MAX_T = 7;

TEST(ColaPrior, encolarDesencolarPermutaciones) {
    // Encola y desencola probando todas las permutaciones
    // posibles de t elementos para t = 1..MAX_T.
    for (int t = 1; t <= MAX_T; t++) {
        vector<int> v;
        int t_factorial = 1;
        for (int i = 1; i <= t; i++) {
            v.push_back(i);
            t_factorial *= i;
        }
        for (int i = 1; i <= t_factorial; i++) {
            ColaPrior<int> q(false);
            for (int j = 0; j < t; j++) {
                q.encolar(v[j]);
            }
            for (int j = t; j > 0; j--) {
                ASSERT_EQ(q.proximo(), j);
                q.desencolar();
	    }
            siguiente_permutacion(v, i);
        }
    }
}

const int NCLAVES = 1000;

int clave(int i) {
	return NCLAVES * ((i * i - 100 * i) % NCLAVES) + i;
}

TEST(ColaPrior, encolarDesencolar1000) {
    vector<int> v;
    for (int i = 0; i < NCLAVES; i++) {
	    v.push_back(clave(i));
    }
    sort(v.begin(), v.end());
    ColaPrior<int> q(false);
    for (int i = 0; i < NCLAVES; i++) {
        q.encolar(clave(i));
    }
    for (int i = NCLAVES; i > 0; i--) {
        ASSERT_EQ(q.proximo(), v[i - 1]);
        q.desencolar();
    }
}
