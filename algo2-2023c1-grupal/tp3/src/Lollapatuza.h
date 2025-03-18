#ifndef LOLLAPATUZA_H
#define LOLLAPATUZA_H

#include <map>
#include <set>
#include "tipos.h"
#include "Puesto.h"
#include "ColaPrior.h"
#include "Gasto.h"

using namespace std;
using itPuesto = map<IdPuesto, Puesto>::iterator;


class Lollapatuza {
public:
    Lollapatuza(const map<IdPuesto, Puesto>& ps, const set<Persona>& as);
    void registrarCompra(IdPuesto p, Persona a, Producto i, Nat c);
    void hackearSistema(Persona a, Producto i);
    Nat getGastoTotalPorPersona(Persona a) const;
    Persona getPersonaQueMasGasto() const;
    IdPuesto getPuestoConMenorStock(Producto i) const;
    const set<Persona>& getPersonasEnSistema() const;
    const map<IdPuesto, Puesto>& getPuestosDeComidaEnSistema() const;

    Lollapatuza(const Lollapatuza& aCopiar);
    Lollapatuza& operator=(const Lollapatuza& d);
private:
    map<IdPuesto, Puesto> puestos;
    set<Persona> personas;
    map<Persona, Nat> gastoPorPersona;
    ColaPrior<Gasto> personaQueMasGasto;
    map<Persona, map<Producto, map<IdPuesto, pair<itPuesto, Nat>>>> puestosHackeablesPorPersona;
};

#endif
