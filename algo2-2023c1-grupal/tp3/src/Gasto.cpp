#include "Gasto.h"

Gasto::Gasto(Nat g, Nat p): gasto(g), per(p) {}

Gasto::Gasto(const Gasto& aCopiar): Gasto(0, 0) {
    *this = aCopiar;
}

Gasto& Gasto::operator=(const Gasto& d) {
    gasto = d.gasto;
    per = d.per;
    return *this;
};

bool Gasto::operator<(const Gasto& l) const {
    if (gasto != l.gasto) {
        return gasto < l.gasto;
    }
    return per > l.per;
}
bool Gasto::operator>(const Gasto& l) const {
    return !(*this == l) && !(*this < l);
}

bool Gasto::operator<=(const Gasto& l) const {
    return (l < *this) || (l == *this);
}

bool Gasto::operator>=(const Gasto& l) const {
    return !(*this < l);
}

bool Gasto::operator==(const Gasto& l) const {
    return gasto == l.gasto && per == l.per;
}

bool Gasto::operator!=(const Gasto& l) const {
    return !(*this == l);
}
