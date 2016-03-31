#include "WidgetAdmin.h"
#include "UtenteBasic.h"
#include "UtenteBusiness.h"
#include "UtenteExecutive.h"
#include <typeinfo>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

WidgetAdmin::WidgetAdmin(QWidget* parent): WidgetUtente(parent) {
    addut = new QPushButton("+",this);
    addut->setToolTip("Aggiungi Utente");
    addut->setFixedSize(30,30);
    sm_r = new QSignalMapper(this);
    sm_m = new QSignalMapper(this);
    sm_l = new QSignalMapper(this);
    sm_c = new QSignalMapper(this);
    QWidget::connect(sm_c,SIGNAL(mapped(int)),this,SLOT(conferma(int)));
    tw = new QTableWidget(this);
    tw->setMinimumSize(600,200);
    QStringList titolo;
    titolo<<""<<"Username"<<"Tipo"<<"Nome"<<"Cognome"<<"Email"<<"Contatti"<<"";
    tw->setColumnCount(8);
    tw->setRowCount(0);
    tw->setHorizontalHeaderLabels(titolo);
    QVBoxLayout* vl = new QVBoxLayout;
    vl->addWidget(tw);
    setLayout(vl);
    tw->show();
}

void WidgetAdmin::addriga() {
    tw->insertRow(tw->rowCount());
}

void WidgetAdmin::removeriga(int r) {
    lia->remove(tw->item(r,1)->text());
    tw->removeRow(r);
    adjustsm();
}

void WidgetAdmin::modriga(int m) {
    QString s;
    tw->removeCellWidget(m,(tw->columnCount())-1);
    QPushButton* conf = new QPushButton("Conferma",tw);
    conf->setStyleSheet("QPushButton {background-color:#1E90FF; border-style: outset;border-width: 1px;border-radius: 5px;border-color: gray;} QPushButton:hover {background-color:#00BFFF} QPushButton:pressed {background-color:#4169E1}");
    tw->setCellWidget(m,(tw->columnCount())-1,conf);
    QWidget::connect(conf,SIGNAL(clicked()),sm_c,SLOT(map()));
    sm_c->setMapping(conf,m);
    for(int i=3;i<6;++i) {
            if(i==5)
                email=tw->item(m,i)->text();
            s = tw->item(m,i)->text();
            tw->item(m,i)->setText("");
            QLineEdit* le = new QLineEdit(s,tw);
            tw->setCellWidget(m,i,le);
            sm_l->setMapping(le,i);
    }
    tipo=tw->item(m,2)->text();
    QComboBox* cbu = new QComboBox();
    cbu->addItem("Utente Basic");
    cbu->addItem("Utente Business");
    cbu->addItem("Utente Executive");
    cbu->setCurrentText(tipo);
    tw->setCellWidget(m,2,cbu);
    for(int r=0;r<(tw->rowCount());++r) {
        tw->cellWidget(r,0)->setEnabled(false);
        if(r != m)
        tw->cellWidget(r,tw->columnCount()-1)->setEnabled(false);
    }
    QString c="";
    QComboBox* lc = dynamic_cast<QComboBox*>(tw->cellWidget(m,6));
    if(lc)
        for(int x=1;x<(lc->count());++x)
        c += lc->itemText(x)+";";
    tw->removeCellWidget(m,6);
    QLineEdit* qle = new QLineEdit(c,tw);
    tw->setCellWidget(m,6,qle);
}

void WidgetAdmin::conferma(int c) {
    bool errore=true;
    try{ errore=controlla_modifica(c); }
    catch(campo_vuoto) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Il campo email non può essere vuoto",QMessageBox::Ok,this);
        mb->show();
    }
    catch(errore_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Formato email non corretto",QMessageBox::Ok,this);
        mb->show();
    }
    catch(errore_contatti) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Alcuni contatti che si vogliono inserire  non sono presenti nel database",QMessageBox::Ok,this);
        mb->show();
    }

    if(!errore) {
        QString s;
        for(int i=3;i<6;++i) {
            QLineEdit* l = dynamic_cast<QLineEdit*>(tw->cellWidget(c,i));
            if(l) {
                s = l->text();
                tw->removeCellWidget(c,i);
                tw->item(c,i)->setText(s);
            }
        }
        QComboBox* pc = dynamic_cast<QComboBox*>(tw->cellWidget(c,2));
        int ind_tipo = pc->currentIndex();
        s = pc->currentText();
        tw->removeCellWidget(c,2);
        tw->item(c,2)->setText(s);
        QComboBox* cbx = new QComboBox();
        cbx->addItem("Lista contatti");
        QLineEdit* l = dynamic_cast<QLineEdit*>(tw->cellWidget(c,6));
        QStringList lista;
        lista = l->text().split(";");
        if (lista.last()=="")
            lista.removeLast();
        for(int l=0;l<lista.size();++l) {
            cbx->addItem(lista[l]);
            cbx->setItemData(l+1,0,Qt::UserRole - 1);
        }
        tw->removeCellWidget(c,6);
        tw->setCellWidget(c,6,cbx);
        tw->removeCellWidget(c,(tw->columnCount())-1);
        QPushButton* mod = new QPushButton("Modifica",tw);
        tw->setCellWidget(c,(tw->columnCount())-1,mod);
        QWidget::connect(mod,SIGNAL(clicked()),sm_m,SLOT(map()));
        sm_m->setMapping(mod,c);
        for(int r=0;r<(tw->rowCount());++r) {
            tw->cellWidget(r,0)->setEnabled(true);
            tw->cellWidget(r,tw->columnCount()-1)->setEnabled(true);
        }
        if(tw->item(c,2)->text()!=tipo)
            lia->changeSubscriptionType(tw->item(c,1)->text(),ind_tipo+1);
        Utente* ut = lia->find(tw->item(c,1)->text());
        if(tw->item(c,5)->text()!=email)
            ut->pf.modificaProfilo(tw->item(c,5)->text());
        ut->rete->net.clear();
        for(int i=0;i<lista.size();++i)
            ut->rete->add(lista[i],*(lia->db));
    }
}

QPushButton* WidgetAdmin::getAdd() const {
    return addut;
}

QTableWidget* WidgetAdmin::getTable() const {
    return tw;
}

QSignalMapper* WidgetAdmin::getSm_r() const {
    return sm_r;
}

QSignalMapper* WidgetAdmin::getSm_m() const {
    return sm_m;
}

QSignalMapper* WidgetAdmin::getSm_l() const {
    return sm_l;
}

QSignalMapper* WidgetAdmin::getSm_c() const {
    return sm_c;
}

void WidgetAdmin::enableadd() {
    addut->setEnabled(true);
}

void WidgetAdmin::addutente() {
    addut->setEnabled(false);
    cu = new CreazioneUtente(this);
    cu->setFixedSize(315,450);
    setMinimumSize(650,500);
    cu->show();
    QHBoxLayout* hb = new QHBoxLayout;
    hb->addWidget(cu,0,Qt::AlignTop);
    hb->addWidget(tw);
    if(layout())
        delete layout();
    setLayout(hb);
    QWidget::connect(cu->getOk(),SIGNAL(clicked()),this,SLOT(enableadd()));
    QWidget::connect(cu->getOk(),SIGNAL(clicked()),this,SLOT(completaadd()));
}

void WidgetAdmin::completaadd() {
    bool errore=true;
    try{ errore=controlla_inserisci(); }
    catch(campo_vuoto) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","I campi contrassegnati da * non possono essere lasciati vuoti",QMessageBox::Ok,this);
        mb->show();
    }
    catch(username_esistente) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Username già in uso",QMessageBox::Ok,this);
        mb->show();
        cu->getUser()->setText("");
    }
    catch(errore_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Formato email non corretto",QMessageBox::Ok,this);
        mb->show();
        cu->getEmail()->setText("");
        cu->getConfEmail()->setText("");
    }
    catch(errore_conf_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Le email non corrispondono",QMessageBox::Ok,this);
        mb->show();
        cu->getEmail()->setText("");
        cu->getConfEmail()->setText("");
    }
    catch(errore_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","La password deve essere almeno di 8 caratteri",QMessageBox::Ok,this);
        mb->show();
        cu->getPaswd()->setText("");
        cu->getConfPaswd()->setText("");
    }
    catch(errore_conf_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Le password non corrispondono",QMessageBox::Ok,this);
        mb->show();
        cu->getPaswd()->setText("");
        cu->getConfPaswd()->setText("");
    }
    catch(errore_contatti) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Alcuni contatti che si vogliono inserire  non sono presenti nel database",QMessageBox::Ok,this);
        mb->show();
    }

    if(!errore) {
        QString u = cu->getUser()->text();
        QString t = cu->getTipo()->currentText();
        QString n = cu->getNome()->text();
        QString c = cu->getCogn()->text();
        QString e = cu->getEmail()->text();
        QStringList cont;
        cont = cu->getContat()->toPlainText().split(";");
        QComboBox* cbc = new QComboBox();
        cbc->addItem("Lista contatti");
        for(int i=0;i<cont.size();++i) {
            cbc->addItem(cont[i]);
            cbc->setItemData(i+1,0,Qt::UserRole - 1);
        }
        addriga();
        QPushButton* rem = new QPushButton("X", tw);
        rem->setToolTip("<font style =\"font:normal;color:black\">rimuovi Utente</font>");
        QPushButton* mod = new QPushButton("Modifica",tw);
        rem->setStyleSheet("color: red; font: bold");
        tw->setCellWidget((tw->rowCount())-1, 0, rem);
        tw->setCellWidget((tw->rowCount())-1,(tw->columnCount())-1,mod);
        adjustsm();
        tw->setItem((tw->rowCount())-1, 1, new QTableWidgetItem(u));
        tw->setItem((tw->rowCount())-1, 2, new QTableWidgetItem(t));
        tw->setItem((tw->rowCount())-1, 3, new QTableWidgetItem(n));
        tw->setItem((tw->rowCount())-1, 4, new QTableWidgetItem(c));
        tw->setItem((tw->rowCount())-1, 5, new QTableWidgetItem(e));
        tw->setCellWidget(tw->rowCount()-1,6, cbc);
        lia->insert(u,cu->getTipo()->currentIndex()+1,e,n,c);
        Utente* ut = lia->find(u);
        for(int i=0;i<cont.size();++i)
            ut->rete->add(cont[i],*(lia->db));
        cu->close();
    }
}

bool WidgetAdmin::controlla_inserisci() {
    if(cu->getUser()->text()=="")
        throw campo_vuoto();
    else if(lia->find((cu->getUser()->text())))
        throw username_esistente();
    else if (cu->getEmail()->text()=="")
        throw campo_vuoto();
    else if(!(cu->getEmail()->text().contains(QRegExp("^[a-zA-Z0-9-_.]+@[a-zA-Z0-9-_.]+.\\bcom\\b|\\bit\\b$"))))
        throw errore_email();
    else if(cu->getEmail()->text()!=cu->getConfEmail()->text())
        throw errore_conf_email();
    else if(cu->getPaswd()->text().size()<8)
        throw errore_pwd();
    else if (cu->getPaswd()->text()!=cu->getConfPaswd()->text())
        throw errore_conf_pwd();
    else {
        QStringList cont;
        cont = cu->getContat()->toPlainText().split(";");
        for(int i=0;i<cont.size();++i) {
            if(!(lia->find(cont[i])))
                throw errore_contatti();
        }
        return false;
    }
}

bool WidgetAdmin::controlla_modifica(int r) {
    QLineEdit* le = dynamic_cast<QLineEdit*>(tw->cellWidget(r,5));
    if (le->text()=="") {
        le->setText(email);
        throw campo_vuoto();
    }
    else if(!(le->text().contains(QRegExp("^[a-zA-Z0-9-_.]+@[a-zA-Z0-9-_.]+.\\bcom\\b|\\bit\\b$")))) {
        le->setText(email);
        throw errore_email();
    } else {
        QLineEdit* lc = dynamic_cast<QLineEdit*>(tw->cellWidget(r,6));
        QStringList lista;
        lista = lc->text().split(";");
        for(int i=0;i<lista.size();++i) {
            if(lista[i]!="")
                if(!(lia->find(lista[i])))
                    throw errore_contatti();
        }
        return false;
    }
}

void WidgetAdmin::mostradb() {
    lia = new LinQedInAdmin();
    QList<SmartUtente>::const_iterator it = lia->db->db.begin();
    tw->setColumnWidth(0,50);
    for( ; it != lia->db->db.end(); ++it) {
        addriga();
        QPushButton* rem = new QPushButton("X", tw);
        rem->setToolTip("<font style =\"font:normal;color:black\">rimuovi Utente</font>");
        rem->setStyleSheet("color: red; font: bold");
        tw->setCellWidget((tw->rowCount())-1, 0, rem);
        QWidget::connect(rem,SIGNAL(clicked()),sm_r,SLOT(map()));
        sm_r->setMapping(rem, (tw->rowCount())-1);
        QPushButton* mod = new QPushButton("Modifica",tw);
        tw->setCellWidget((tw->rowCount())-1,(tw->columnCount())-1,mod);
        QWidget::connect(mod,SIGNAL(clicked()),sm_m,SLOT(map()));
        sm_m->setMapping(mod, (tw->rowCount())-1);
        tw->setItem((tw->rowCount())-1, 1, new QTableWidgetItem(it->u->un.login));
        tw->item((tw->rowCount())-1,1)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        if(typeid(*(it->u))==typeid(UtenteBasic))
            tw->setItem((tw->rowCount())-1, 2, new QTableWidgetItem("Utente Basic"));
        else if(typeid(*(it->u))==typeid(UtenteBusiness))
            tw->setItem((tw->rowCount())-1, 2, new QTableWidgetItem("Utente Business"));
        else if(typeid(*(it->u))==typeid(UtenteExecutive))
            tw->setItem((tw->rowCount())-1, 2, new QTableWidgetItem("Utente Executive"));
        tw->item((tw->rowCount())-1,2)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tw->setItem((tw->rowCount())-1, 3, new QTableWidgetItem(it->u->pf.getProfilo()->getNome()));
        tw->item((tw->rowCount())-1,3)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tw->setItem((tw->rowCount())-1, 4, new QTableWidgetItem(it->u->pf.getProfilo()->getCognome()));
        tw->item((tw->rowCount())-1,4)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tw->setItem((tw->rowCount())-1, 5, new QTableWidgetItem(it->u->pf.getProfilo()->getEmail()));
        tw->item((tw->rowCount())-1,5)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QComboBox* cb = new QComboBox();
        cb->addItem("Lista contatti");
        int i=1;
        QList<Username>::const_iterator it_rete = (it->u->rete->net).begin();
        for( ; it_rete != (it->u->rete->net).end();  ++it_rete,++i) {
            cb->addItem(it_rete->login);
            tw->setColumnWidth(6,140);
            cb->setItemData(i,0,Qt::UserRole - 1);
        };
        tw->setCellWidget(tw->rowCount()-1,6, cb);
    }
    tw->setColumnWidth(2,150);
    tw->setColumnWidth(5,200);
    QWidget::connect(sm_r,SIGNAL(mapped(int)),this,SLOT(removeriga(int)));
    QWidget::connect(sm_m,SIGNAL(mapped(int)),this,SLOT(modriga(int)));
    QWidget::connect(addut,SIGNAL(clicked()),this, SLOT(addutente()));
}

void WidgetAdmin::adjustsm() {
    delete sm_r;
    delete sm_m;
    sm_r = new QSignalMapper(this);
    sm_m = new QSignalMapper(this);
    for(int i=0;i<tw->rowCount();++i) {
        QWidget* order_r = tw->cellWidget(i,0);
        QWidget* order_m = tw->cellWidget(i,(tw->columnCount())-1);
        QWidget::connect(order_r,SIGNAL(clicked()),sm_r,SLOT(map()));
        QWidget::connect(order_m,SIGNAL(clicked()),sm_m,SLOT(map()));
        sm_r->setMapping(order_r, i);
        sm_m->setMapping(order_m, i);
    }
    QWidget::connect(sm_r,SIGNAL(mapped(int)),this,SLOT(removeriga(int)));
    QWidget::connect(sm_m,SIGNAL(mapped(int)),this,SLOT(modriga(int)));
}

void WidgetAdmin::save() {
    if(lia) {
        lia->save();
        QMessageBox* mb = new QMessageBox(QMessageBox::Information,"LinQedIn","Salvataggio completato",QMessageBox::Ok,this);
        mb->show();
    }
    else {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"LinQedIn","Prima carica il database",QMessageBox::Ok,this);
        mb->show();
    }
}
