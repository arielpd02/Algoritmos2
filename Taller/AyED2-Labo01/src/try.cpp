//
// Created by Ariel on 27/06/2023.

#include "Puesto.h"


Puesto& Puesto::operator=(const Puesto& p) {
    this->promos=p.promos;
    this->stock=p.stock;
    this->menu=p.menu;
    this->ventas=p.ventas;
    this->ventasHackeables=p.ventasHackeables;
    this->gastosPorPersonaEnPuesto=p.gastosPorPersonaEnPuesto;
    return *this;
}

