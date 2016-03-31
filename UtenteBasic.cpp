#include "UtenteBasic.h"
#include <QTableWidget>
#include <QList>

UtenteBasic::UtenteBasic(Username u): Utente(u) {}

UtenteBasic::~UtenteBasic() {}

// overriding: ricerca per un utente Basic, funtore di tipo 1
QTableWidget* UtenteBasic::userSearch(const DB & d,const Username& us) const {
    QTableWidget* tw = new QTableWidget();
    QStringList titolo;
    titolo<<"Username"<<"Nome"<<"Cognome";
    tw->setColumnCount(3);
    tw->setRowCount(0);
    tw->setHorizontalHeaderLabels(titolo);
    tw->setShowGrid(false);
    if(us.login=="") {
        QList<SmartUtente>::const_iterator it = d.db.begin();
        for(;it!=d.db.end();++it) {
            if(it->u->un.login != un.login) {
                SearchFunctor cerca(1);
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
        SearchFunctor cerca(1);
        cerca(*su, tw);
        }
    }
    return tw;
}

//overriding metodo clone utente Basic
UtenteBasic* UtenteBasic::clone() const {
    return new UtenteBasic(*this); // costruttore di copia standard di UtenteBasic (*this ha tipo UtenteBasic)
}

//overriding metodo che ritorna il tipo come intero utente Basic
int UtenteBasic::getTipo() const {
    return 1;
}
