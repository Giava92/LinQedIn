#ifndef DB_H
#define DB_H

#include "SmartUtente.h"
#include <QList>

class Utente;

class SmartUtente;

// il database di utenti LinQedIn
class DB {
public:
    QList<SmartUtente> db;
    void load();
    // carica da file
    void save() const; // salva su file
    // cerca l'utente (con il suo tipo)
    // avente Username u nel DB
    Utente* find(Username) const;
    void insert(Username, int,QString,QString,QString);
};

#endif // DB_H
