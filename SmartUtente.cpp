#include "SmartUtente.h"

SmartUtente::SmartUtente(Utente* ut): u(ut) {}

SmartUtente::~SmartUtente() {
    if(!u)
        delete u;
}

bool SmartUtente::operator ==(const SmartUtente& su) const {
    return u == su.u;
}
