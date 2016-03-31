#ifndef RETE_H
#define RETE_H

#include "SmartUtente.h"
#include "Username.h"
#include "DB.h"
#include <QList>

class SmartUtente;

class DB;

class Rete {
public:
    QList<Username> net;
    void add(Username, const DB&);
    int remove(Username);
    Rete();
};

#endif // RETE_H
