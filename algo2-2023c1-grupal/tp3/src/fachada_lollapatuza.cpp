#include <map>
#include "fachada_lollapatuza.h"

FachadaLollapatuza::FachadaLollapatuza(
        const set<Persona> &personas, const map<IdPuesto, aed2_Puesto> &infoPuestos
) : lolla(Lollapatuza(construirPuestos(infoPuestos), personas)) {}

void FachadaLollapatuza::registrarCompra(Persona persona, Producto producto, Nat cant, IdPuesto idPuesto) {
    lolla.registrarCompra(idPuesto,persona,producto,cant);
}

void FachadaLollapatuza::hackear(Persona persona, Producto producto) {
    lolla.hackearSistema(persona,producto);
}

Nat FachadaLollapatuza::gastoTotal(Persona persona) const {
    Nat res = lolla.getGastoTotalPorPersona(persona);
    return res;
}

Persona FachadaLollapatuza::mayorGastador() const {
    return lolla.getPersonaQueMasGasto();
}

IdPuesto FachadaLollapatuza::menorStock(Producto producto) const {
   return lolla.getPuestoConMenorStock(producto);
}

const set<Persona> &FachadaLollapatuza::personas() const {
    return lolla.getPersonasEnSistema();
}

Nat FachadaLollapatuza::stockEnPuesto(IdPuesto idPuesto, const Producto &producto) const {
    Puesto puesto = lolla.getPuestosDeComidaEnSistema().at(idPuesto);
    return puesto.getStock(producto);
}

Nat FachadaLollapatuza::descuentoEnPuesto(IdPuesto idPuesto, const Producto &producto, Nat cantidad) const {
    Puesto puesto = lolla.getPuestosDeComidaEnSistema().at(idPuesto);
    return puesto.getDescuento(producto,cantidad);
}

Nat FachadaLollapatuza::gastoEnPuesto(IdPuesto idPuesto, Persona persona) const {
    Puesto puesto = lolla.getPuestosDeComidaEnSistema().at(idPuesto);
    return puesto.getGastoPorPersonaEnPuesto(persona);
}

set<IdPuesto> FachadaLollapatuza::idsDePuestos() const {
    set<IdPuesto> idsPuestos;
    map<IdPuesto, Puesto> puestosConId = lolla.getPuestosDeComidaEnSistema();
    for( auto p : puestosConId){
        idsPuestos.insert(p.first);
    }
    return idsPuestos;
}

map<IdPuesto, Puesto> FachadaLollapatuza::construirPuestos(const map<IdPuesto, aed2_Puesto> &infoPuestos) const {
    map<IdPuesto, Puesto> puestos;
    for (const auto& p : infoPuestos) {
        puestos.insert({
            p.first,
                Puesto(
                    p.second.menu,
                    p.second.stock,
                    p.second.promociones
                )
        });
    }
    return puestos;
}