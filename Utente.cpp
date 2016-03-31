#include "Utente.h"
#include <QList>
#include <QComboBox>
#include <QListWidget>
#include <QStandardItemModel>

Utente::Utente(Username u): un(u) {
    rete = new Rete();
};

Utente::~Utente() {
    if(!rete)
        delete rete;
}

Utente::SearchFunctor::SearchFunctor(int x=0): searchType(x) {}

void Utente::SearchFunctor::operator () (const SmartUtente& x, QTableWidget* tw) const {
    switch(searchType) {
        case 1:
            tw->insertRow(tw->rowCount());
            tw->setItem(tw->rowCount()-1,0,new QTableWidgetItem(x.u->un.login));
            tw->setItem(tw->rowCount()-1,1,new QTableWidgetItem(((x.u)->pf).getProfilo()->getNome()));
            tw->setItem(tw->rowCount()-1,2,new QTableWidgetItem(((x.u)->pf).getProfilo()->getCognome()));
            tw->setMinimumWidth(420);
            break;
        case 2:
            tw->insertRow(tw->rowCount());
            tw->setItem(tw->rowCount()-1,0,new QTableWidgetItem(x.u->un.login));
            tw->setItem(tw->rowCount()-1,1,new QTableWidgetItem(((x.u)->pf).getProfilo()->getNome()));
            tw->setItem(tw->rowCount()-1,2,new QTableWidgetItem(((x.u)->pf).getProfilo()->getCognome()));
            tw->setItem(tw->rowCount()-1,3,new QTableWidgetItem(((x.u)->pf).getProfilo()->getEmail()));
            tw->setColumnWidth(3,140);
            tw->setMinimumWidth(560);
            break;
        case 3:
        {
            tw->insertRow(tw->rowCount());
            tw->setItem(tw->rowCount()-1,0,new QTableWidgetItem(x.u->un.login));
            tw->setItem(tw->rowCount()-1,1,new QTableWidgetItem(((x.u)->pf).getProfilo()->getNome()));
            tw->setItem(tw->rowCount()-1,2,new QTableWidgetItem(((x.u)->pf).getProfilo()->getCognome()));
            tw->setItem(tw->rowCount()-1,3,new QTableWidgetItem(((x.u)->pf).getProfilo()->getEmail()));
            tw->setColumnWidth(3,180);
            QComboBox* cb = new QComboBox();
            cb->addItem("Lista contatti");
            int i=1;
            QList<Username>::const_iterator it = (((x.u)->rete)->net).begin();
            for( ; it != (((x.u)->rete)->net).end();  ++it,++i) {
                cb->addItem(it->login);
                cb->setItemData(i,0,Qt::UserRole - 1);
            };
            tw->setCellWidget(tw->rowCount()-1,4, cb);
            tw->setColumnWidth(4,140);
            tw->setMinimumWidth(740);
            break;
        }
        default:
            tw->insertRow(tw->rowCount());
            tw->setItem(tw->rowCount()-1,0,new QTableWidgetItem(x.u->un.login));
        }
}
