#ifndef SMARTUTENTE_H
#define SMARTUTENTE_H

#include "Utente.h"

class Utente;

class SmartUtente {
public:
    Utente* u; // puntatore polimorfo
    SmartUtente(Utente* ut=0);
    ~SmartUtente();
    bool operator==(const SmartUtente&) const;
};

#endif // SMARTUTENTE_H
