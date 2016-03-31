#ifndef LINQEDINCLIENT_H
#define LINQEDINCLIENT_H

#include "DB.h"

// lato client

class LinQedInClient {
public:
    Utente* u;
    DB* db; // inizializzato da file
    // usato in sola lettura
    LinQedInClient(Username);
    void aggiornaProfilo(QString, QString n="", QString c="");
    void showProfilo();
    void insertRete(Username);
    void removeRete(Username);
    // funzionalita` di ricerca autorizzata per u
    QTableWidget* ricerca(Username un);
    void save() const;
};

#endif // LINQEDINCLIENT_H
