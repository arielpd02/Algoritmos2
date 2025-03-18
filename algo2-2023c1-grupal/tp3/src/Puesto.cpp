#include "Puesto.h"

Puesto::Puesto(const Menu &m, const Stock &s, const Promociones &p):
    menu(m), stock(s), promos(construirPromos(p)) {}

Menu Puesto::getMenu() const {
    // TODO Fermin: ojo que devuelven una copia; podía ser una referencia constante y tenía menos complejidad (O(1))
    return menu;
}
Nat Puesto::getStock(Producto i) const {
    return stock.at(i);
}
Nat Puesto::getDescuento(Producto i, Nat c) const {
    // TODO Fermin: lindo código; prolijo!
    if (promos.count(i)) {
        vector<Nat> descuentos = promos.at(i);
        if (c >= descuentos.size()) {
            return descuentos.back();
        } else {
            return descuentos[c];
        }
    } else {
        return 0;
    }
}

Nat Puesto::getGastoPorPersonaEnPuesto(Persona a) const {
    if (gastosPorPersonaEnPuesto.count(a)) {
        return gastosPorPersonaEnPuesto.at(a);
    } else {
        return 0;
    }
}

void Puesto::registrarCompraEnPuesto(Persona a, Producto i, Nat c) {
    // TODO Fermin: es mejor si utilizan nombres descriptivos para los parámetros, se entiende más
    //  (aunque estén los tipos, estos no se leen más abajo)
    itLista it = agregarVenta(a, i, c);

    // Si es hackeable la agregamos a ventasHackeables
    if (getDescuento(i, c) == 0) {
        agregarVentaHackeable(a, i, it);
    }

    // Calculamos el total y actualizamos el gasto para esa persona
    Nat total = calcularTotal(i, c);
    if (gastosPorPersonaEnPuesto.count(a)) {
        total += gastosPorPersonaEnPuesto[a];
    }
    gastosPorPersonaEnPuesto[a] = total;

    // Actualizamos stock
    // TODO Fermin: recuerden que [] (y at) devuelve una referencia modificable; podían hacer stock[i] -= c
    Nat s = stock[i] - c;
    stock[i] = s;
}

void Puesto::hackearPuesto(Persona a, Producto i) {
    // TODO Fermin: muy lindo código; muy prolijo
    stock[i] += 1;
    Nat precio = menu[i];
    Nat gasto = gastosPorPersonaEnPuesto[a] - precio;
    // TODO Fermin: lo que hacen con stock, lo podían hacer acá con el precio (y se ahorraban una/dos línea/s)
    gastosPorPersonaEnPuesto[a] = gasto;
    olvidarItem(a, i);
}

Nat Puesto::calcularTotal(Producto i, Nat c) {
    Nat descuento = getDescuento(i, c);
    Nat precio = menu[i];
    return aplicarDescuento(c * precio, descuento);
}
Puesto::Puesto(const Puesto& aCopiar){
    *this=aCopiar;
}
Puesto& Puesto::operator=(const Puesto& aCopiar){
       menu=aCopiar.menu;
       stock=aCopiar.stock;
       promos=aCopiar.promos;
       ventas=aCopiar.ventas;
       ventasHackeables=aCopiar.ventasHackeables;
       gastosPorPersonaEnPuesto=aCopiar.gastosPorPersonaEnPuesto;
       return *this;
}


/************** Auxiliares ****************/

Nat Puesto::aplicarDescuento(Nat p, Nat d) {
    return p - (p * (d / 100.0));
}

map<Producto, vector<Nat>> Puesto::construirPromos(const Promociones& ps) const {
    map<Producto,vector<Nat>> res;
    auto it = ps.begin();
    while (it != ps.end()) {
        Producto prod = it->first;
        vector<Nat> promosV = construirPromosParaItem(it->second);
        res[prod] = promosV;
        it++;
    }
    return res;
}

vector<Nat> Puesto::construirPromosParaItem(const map<Nat, Nat>& ps) const {
    vector<Nat> res;
    res.push_back(0);  // Puesto que no nos interesa la pos 0
    Nat max = maxPromosParaItem(ps);
    Nat mejorPromo = 0;
    for (int cant = 1; cant <= max ; cant++) {
        if (ps.count(cant)) {
            mejorPromo = ps.at(cant);
        }
        res.push_back(mejorPromo);
    }
    return res;
}

Nat Puesto::maxPromosParaItem(const map<Nat, Nat>& ps) const {
    Nat res = 0;
    for (pair<Nat, Nat> p : ps) {
        if (p.first > res) {
            res = p.first;
        }
    }
    return res;
}

itLista Puesto::agregarVenta(Persona p, Producto i, Nat c) {
    pair<Producto ,Nat> venta(i, c);
    ventas[p].push_back(venta);
    auto it = ventas[p].end();
    it--;
    return it;
}

void Puesto::agregarVentaHackeable(Persona p, Producto i, itLista it) {
    ventasHackeables[p][i].push_back(it);
}

void Puesto::olvidarItem(Persona p, Producto i) {
    auto it = ventasHackeables[p][i].front();
    if (it->second > 1) {
        // Borramos un solo item de la venta
        it->second = it->second - 1;
    } else {
        // Borramos la venta de la persona y el iterador de la lista
        ventas[p].erase(it);
        ventasHackeables[p][i].pop_front();
    }
}
