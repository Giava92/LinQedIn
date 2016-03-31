#include "LinQedInAdmin.h"
#include "UtenteBasic.h"
#include "UtenteBusiness.h"
#include "UtenteExecutive.h"

LinQedInAdmin::LinQedInAdmin() {
    // carica da file
    db = new DB();
    db->load();
}

void LinQedInAdmin::insert(Username u, int i,QString e,QString n,QString c) {
    db->insert(u,i,e,n,c);
}

Utente* LinQedInAdmin::find(Username u) const {
    return db->find(u);
}

void LinQedInAdmin::remove(Username u) {
    int index;
    QList<SmartUtente>::const_iterator it = db->db.begin();
    for(int i=0;it<db->db.end();++it, ++i) {
        if(it->u->un == u)
            index=i;
    }
    db->db.removeAt(index);
}

void LinQedInAdmin::changeSubscriptionType(Username u, int i) {
    Utente* ut = db->find(u);
    Utente* utp;
    if(ut->getTipo()!= i)
        switch (i) {
        case 1:
            utp = new UtenteBasic(u);
            break;
        case 2:
            utp = new UtenteBusiness(u);
            break;
        case 3:
            utp = new UtenteExecutive(u);
            break;
        default:
            utp = new UtenteBasic(u);
            break;
        }
    utp->pf = ut->pf;
    utp->rete = ut->rete;
    int index;
    QList<SmartUtente>::const_iterator it = db->db.begin();
    for(int i=0;it<db->db.end();++it, ++i) {
        if(it->u->un == u)
            index=i;
    }
    SmartUtente sun = SmartUtente(utp);
    db->db.replace(index,sun);
}

void LinQedInAdmin::save() const {
    db->save();
}
