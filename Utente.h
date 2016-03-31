#ifndef UTENTE_H
#define UTENTE_H

#include "Profilo.h"
#include "Rete.h"
#include "Username.h"
#include "DB.h"
#include <QTableWidget>

class DB;

class Rete;

// base astratta e polimorfa
class Utente {
public:
    Rete* rete;
    Username un;
    Profilo pf;
    Utente(Username);
    virtual ~Utente();
    // ricerca polimorfa, virtuale pura
    // contratto: la ricerca permessa dalla propria tipologia di subscription
    virtual QTableWidget* userSearch(const DB& d, const Username&) const =0;
    virtual Utente* clone() const =0;
    virtual int getTipo() const =0;
    class utente_non_trovato {};
protected:
    // classe annidata di funtori di ricerca
    class SearchFunctor {
    public:
        int searchType;
        SearchFunctor(int);
        void operator() (const SmartUtente&, QTableWidget*) const;
    };
};

#endif // UTENTE_H
