#ifndef PUESTO_H
#define PUESTO_H

#include <map>
#include <list>
#include <vector>
#include "tipos.h"

using namespace std;
using itLista = list<pair<Producto, Nat>>::iterator;

class Puesto {
public:
    Puesto(Menu menu, Stock stock, Promociones promos);

    Menu getMenu();
    Nat getStock(Producto i);
    Nat getDescuento(Producto i, Nat c);
    Nat getGastoPorPersonaEnPuesto(Persona a);
    void registrarCompraEnPuesto(Persona a, Producto i, Nat c);
    void hackearPuesto(Persona a, Producto i);
    Nat calcularTotal(Producto i, Nat c);
    Puesto& operator=(const Puesto& p);

//friend class Lollapatuza; //

private:
    Menu menu;
    Stock stock;
    map<Producto, vector<Nat>> promos;
    map<Persona, list<pair<Producto, Nat>>> ventas;
    map<Persona, map<Producto, list<itLista>>> ventasHackeables;
    map<Persona, Nat> gastosPorPersonaEnPuesto;

    void olvidarItem(Persona p, Producto i);
    map<Producto, vector<Nat>> construirPromos(Promociones promos);
    vector<Nat> construirPromosParaItem(map<Nat, Nat> promos);
    Nat maxPromosParaItem(map<Nat, Nat> promos);
    itLista agregarVenta(Persona p, Producto i, Nat c);
    void agregarVentaHackeable(Persona p, Producto i, itLista it);
    Nat aplicarDescuento(Nat p,Nat d);
};

#endif