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
    Puesto(const Menu &menu, const Stock &stock, const Promociones &promos);
    Menu getMenu() const;
    Nat getStock(Producto i) const;
    Nat getDescuento(Producto i, Nat c) const;
    Nat getGastoPorPersonaEnPuesto(Persona a) const;
    void registrarCompraEnPuesto(Persona a, Producto i, Nat c);
    void hackearPuesto(Persona a, Producto i);
    Nat calcularTotal(Producto i, Nat c);

    Puesto(const Puesto& aCopiar);
    Puesto& operator=(const Puesto& p);
private:
    Menu menu;
    Stock stock;
    map<Producto, vector<Nat>> promos;
    map<Persona, list<pair<Producto, Nat>>> ventas;
    map<Persona, map<Producto, list<itLista>>> ventasHackeables;
    map<Persona, Nat> gastosPorPersonaEnPuesto;

    void olvidarItem(Persona p, Producto i);
    map<Producto, vector<Nat>> construirPromos(const Promociones& promos) const;
    vector<Nat> construirPromosParaItem(const map<Nat, Nat>& promos) const;
    Nat maxPromosParaItem(const map<Nat, Nat>& promos) const;
    itLista agregarVenta(Persona p, Producto i, Nat c);
    void agregarVentaHackeable(Persona p, Producto i, itLista it);
    Nat aplicarDescuento(Nat p,Nat d);
};

#endif