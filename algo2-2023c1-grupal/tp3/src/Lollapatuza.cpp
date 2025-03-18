#include "Lollapatuza.h"

Lollapatuza::Lollapatuza(const map<IdPuesto, Puesto>& ps, const set<Persona>& as) {
    puestos = ps;
    personas = as;
    for (Persona p : as) {
        Gasto g(0, p);
        personaQueMasGasto.encolar(g);
    }
}

Lollapatuza::Lollapatuza(const Lollapatuza& aCopiar): Lollapatuza({}, {}) {
    *this = aCopiar;
}

Lollapatuza& Lollapatuza::operator=(const Lollapatuza& d) {
    // TODO Fermin: no hacía falta implementarlo
    puestos = d.puestos;
    personas = d.personas;
    gastoPorPersona = d.gastoPorPersona;
    puestosHackeablesPorPersona = d.puestosHackeablesPorPersona;
    personaQueMasGasto = d.personaQueMasGasto;
    return *this;
};

Persona Lollapatuza::getPersonaQueMasGasto() const {
    return personaQueMasGasto.proximo().per;
}

Nat Lollapatuza::getGastoTotalPorPersona(Persona a) const {
    if (gastoPorPersona.count(a) >= 1) {
        return gastoPorPersona.at(a);
    }
    return 0;
}

const set<Persona>& Lollapatuza::getPersonasEnSistema() const {
    return personas;
}

const map<IdPuesto,Puesto>& Lollapatuza::getPuestosDeComidaEnSistema() const {
    return puestos;
}

void Lollapatuza::registrarCompra(IdPuesto p, Persona a, Producto i, Nat c) {
    // TODO Fermin: buen código, pero recuerden usar nombres descriptivos para los parámetros
    // Buscamos el puesto por id y registramos la compra
    Puesto& puesto = puestos.at(p);
    puesto.registrarCompraEnPuesto(a, i, c);

    // Nos fijamos y registramos si la compra es hackeable
    bool huboDescuento = (puesto.getDescuento(i, c) > 0); // TODO Fermin: no hacían falta los paréntesis
    if (!huboDescuento) {
        auto it = puestos.find(p);
        int hacks = puestosHackeablesPorPersona[a][i][p].second;
        puestosHackeablesPorPersona[a][i][p] = {it, hacks + c};
    }

    // Procesamos el gasto por persona
    // TODO Fermin: recuerden que pueden usar las referencias y se ahorran un par de accesos innecesarios a la estructura
    Nat viejoGastoTotal = gastoPorPersona[a];
    Nat nuevoGastoTotal = puesto.calcularTotal(i,c) + viejoGastoTotal;
    gastoPorPersona[a] = nuevoGastoTotal;

    // TODO Fermin: esto (y lo de arriba) estaría bueno meterlo en dos métodos apartes, hace más legible al código
    // Mantenemos el max heap
    Gasto gasto = Gasto(viejoGastoTotal,a);
    if (personaQueMasGasto.pertenece(gasto)) {
        personaQueMasGasto.borrar(gasto);
    }
    personaQueMasGasto.encolar(Gasto(nuevoGastoTotal, a));

}
void Lollapatuza::hackearSistema(Persona a, Producto i) {
    // Buscamos el puesto
    map<IdPuesto, pair<itPuesto, Nat>>& puestoHackeables = puestosHackeablesPorPersona[a][i];

    // Apuntamos al primer elemento -> menor clave por iterador de un diccLog
    auto it = puestoHackeables.begin();
    Puesto& p = it->second.first->second;
    Nat& hacks = it->second.second;

    // Hackeamos el puesto y modificamos la cantidad de hackeos posibles
    p.hackearPuesto(a, i);
    hacks--;
    if (hacks == 0) {
        puestoHackeables.erase(it);
    }

    // TODO Fermin: fijense que este código es muy similar al de registrarCompra
    //  más razón para usar métodos y evitar la repetición de código, lo cual es propenso a errores
    //  (ya que cualquier modificación hay que replicarla tantas veces como está repetido el código)
    // Mantenemos actualizados el maxheap y el dicc de gastos por persona
    Nat viejoGasto = gastoPorPersona[a];
    Nat nuevoGasto = viejoGasto - p.calcularTotal(i,1);
    gastoPorPersona[a] = nuevoGasto;
    personaQueMasGasto.borrar(Gasto(viejoGasto, a));
    personaQueMasGasto.encolar(Gasto(nuevoGasto, a));
}

IdPuesto Lollapatuza::getPuestoConMenorStock(Producto i) const{
    // TODO Fermin: el código está bien y es prolijo, pero sería mejor si encapsulan los bulces en métodos ("puestosConItem", "buscarMinimoStock")
    //Nos armamos un diccionario con los puestos con tal item en menú
    map<IdPuesto,Puesto> puestosConItem;
    auto it = puestos.begin();
    while(it != puestos.end()){
        IdPuesto pid = it->first;
        Puesto puesto = it->second;
        if(puesto.getMenu().count(i)){ // TODO Fermin: acá están copiando todo el menú para ver si tiene un item! Implementar "puesto.tieneItem(item)"
            puestosConItem.insert({pid, puesto});
        }
        it++;
    }
    //Si no hay puestos con el item en menu, devolvemos el puesto con menor id
    if(puestosConItem.empty()){
        return puestos.begin()->first;
    }

    //Caso contrario, hay puesto(s) con el item definido, buscamos el minimo y lo desempatamos por id
    auto it1 = puestosConItem.begin();
    Nat min = it1->second.getStock(i);
    IdPuesto min_pid = it1->first;
    it1++;
    while(it1 != puestosConItem.end()){
        IdPuesto pid = it1->first;
        Nat stock = it1->second.getStock(i);
        if( stock < min || (stock == min && pid < min_pid)){
            min = stock;
            min_pid = pid;
        }
        it1++;
    }
    return  min_pid;
}

