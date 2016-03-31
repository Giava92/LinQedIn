#include "UtenteBusiness.h"

UtenteBusiness::UtenteBusiness(Username u): Utente(u) {}

UtenteBusiness::~UtenteBusiness() {}

// overriding: ricerca per un utente Business, funtore di tipo 2
QTableWidget* UtenteBusiness::userSearch(const DB& d,const Username& us) const {
    QTableWidget* tw = new QTableWidget();
    QStringList titolo;
    titolo<<"Username"<<"Nome"<<"Cognome"<<"Email";
    tw->setColumnCount(4);
    tw->setRowCount(0);
    tw->setHorizontalHeaderLabels(titolo);
    tw->setShowGrid(false);
    if(us.login=="") {
        QList<SmartUtente>::const_iterator it = d.db.begin();
        for(;it!=d.db.end();++it) {
            if(it->u->un.login != un.login) {
                SearchFunctor cerca(2);
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
            SearchFunctor cerca(2);
            cerca(*su, tw);
        }
    }
    return tw;
}

//overriding metodo clone utente Business
UtenteBusiness* UtenteBusiness::clone() const {
    return new UtenteBusiness(*this); // costruttore di copia standard di UtenteBusiness (*this ha tipo UtenteBusiness)
}

//overriding metodo che ritorna il tipo come intero utente Business
int UtenteBusiness::getTipo() const {
    return 2;
}
