#include "UtenteExecutive.h"

UtenteExecutive::UtenteExecutive(Username u): Utente(u) {}

UtenteExecutive::~UtenteExecutive() {}

// overriding: ricerca per un utente Executive, funtore di tipo 3
QTableWidget* UtenteExecutive::userSearch(const DB& d,const Username& us) const {
    QTableWidget* tw = new QTableWidget();
    QStringList titolo;
    titolo<<"Username"<<"Nome"<<"Cognome"<<"Email"<<"Contatti";
    tw->setColumnCount(5);
    tw->setRowCount(0);
    tw->setHorizontalHeaderLabels(titolo);
    tw->setShowGrid(false);
    if(us.login=="") {
        QList<SmartUtente>::const_iterator it = d.db.begin();
        for(;it!=d.db.end();++it) {
            if(it->u->un.login != un.login) {
                SearchFunctor cerca(3);
                cerca(*it, tw);
            }
        }
    }
    else {
        Utente* ut=d.find(us);
        if(!ut)
            throw utente_non_trovato();
        else {
            SmartUtente* su = new SmartUtente(ut);
            SearchFunctor cerca(3);
            cerca(*su, tw);
        }
    }
    return tw;
}

//overriding metodo clone utente Executive
UtenteExecutive* UtenteExecutive::clone() const {
    return new UtenteExecutive(*this); // costruttore di copia standard di UtenteExecutive (*this ha tipo UtenteExecutive)
}

//overriding metodo che ritorna il tipo come intero utente Executive
int UtenteExecutive::getTipo() const {
    return 3;
}
