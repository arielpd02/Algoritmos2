#ifndef GASTO_H
#define GASTO_H

#include "tipos.h"

struct Gasto {
    Gasto(Nat g, Nat p);
    int gasto;
    int per;
    bool operator<(const Gasto& l) const;
    bool operator>(const Gasto& l) const;
    bool operator<=(const Gasto& l) const;
    bool operator>=(const Gasto& l) const;
    bool operator==(const Gasto& l) const;
    bool operator!=(const Gasto& l) const;

    Gasto(const Gasto& aCopiar);
    Gasto& operator=(const Gasto& d);
};

#endif