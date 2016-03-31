#ifndef LINQEDINADMIN_H
#define LINQEDINADMIN_H

#include "DB.h"

// lato amministratore

class LinQedInAdmin {
public:
    DB* db; // inizializzato da file
    // gestito in memoria
    // salvabile su file
    LinQedInAdmin();
    void insert(Username, int,QString,QString,QString);
    Utente* find(Username) const;
    void remove(Username);
    // cambia tra Basic, Business, Executive
    void changeSubscriptionType(Username, int);
    void save() const;
};

#endif // LINQEDINADMIN_H
