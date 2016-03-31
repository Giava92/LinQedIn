#include "LinQedInClient.h"

LinQedInClient::LinQedInClient(Username s) {
    // carica il DB
    db = new DB();
    db->load();
    // cerca l'utente client con Username s
    u = db->find(s);
}

void LinQedInClient::aggiornaProfilo(QString e, QString n, QString c) {
    (u->pf).modificaProfilo(e, n, c);
}

void LinQedInClient::showProfilo() {
    (u->pf).getProfilo();
}

void LinQedInClient::insertRete(Username un) {
    u->rete->add(un, *db);
}

void LinQedInClient::removeRete(Username un) {
    u->rete->remove(un);
}

QTableWidget* LinQedInClient::ricerca(Username un) {
    QTableWidget* tw = u->userSearch(*db,un);
    return tw;
}

void LinQedInClient::save() const {
    db->save();
}
