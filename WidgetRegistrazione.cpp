#include "WidgetRegistrazione.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

WidgetRegistrazione::WidgetRegistrazione(QWidget* parent): QWidget(parent) {
    lista = new QList<QLineEdit*>();
    for(int x=0;x<7;++x) {
        lista->append(new QLineEdit(this));
        if(x==5 || x==6)
            (*lista)[x]->setEchoMode(QLineEdit::Password);
    }
    indietro = new QPushButton("Indietro",this);
    indietro->setFixedWidth(80);
    reset = new QPushButton("Reset",this);
    conferma = new QPushButton("Conferma",this);
    QLabel* lu = new QLabel("Username*:",this);
    QLabel* ln = new QLabel("Nome:",this);
    QLabel* lc = new QLabel("Cognome:",this);
    QLabel* le = new QLabel("Email*:", this);
    QLabel* lre = new QLabel("Ripeti Email*:", this);
    QLabel* lp = new QLabel("Password*:",this);
    QLabel* lrp = new QLabel("Ripeti Password*:",this);
    QLabel* lo = new QLabel("I campi contrassegnati da * sono obbligatori",this);
    QGridLayout* grid = new QGridLayout;
    grid->addWidget(lu,1,1);
    grid->addWidget(ln,2,1);
    grid->addWidget(lc,3,1);
    grid->addWidget(le,4,1);
    grid->addWidget(lre,5,1);
    grid->addWidget(lp,6,1);
    grid->addWidget(lrp,7,1);
    for(int x=0; x<7;++x)
        grid->addWidget((*lista)[x],x+1,2);
    grid->addWidget(lo,8,1);
    grid->addWidget(indietro,9,1);
    grid->addWidget(reset,9,2,Qt::AlignLeft);
    grid->addWidget(conferma,9,2,Qt::AlignRight);
    grid->setColumnMinimumWidth(1,1000);
    grid->setColumnMinimumWidth(2,200);
    grid->setColumnStretch(1,3);
    setLayout(grid);
    QWidget::connect(reset,SIGNAL(clicked()),this,SLOT(resetta()));
}

QPushButton* WidgetRegistrazione::getIndietro() const {
    return indietro;
}

QPushButton* WidgetRegistrazione::getReset() const {
    return reset;
}

QPushButton* WidgetRegistrazione::getConferma() const {
    return conferma;
}

QList<QLineEdit*>* WidgetRegistrazione::getlista() const {
    return lista;
}

LinQedInAdmin* WidgetRegistrazione::getr_lia() const {
    return r_lia;
}

void WidgetRegistrazione::resetta() {
    for(int x=0;x<lista->size();++x) {
        (*lista)[x]->setText("");
    }
}

bool WidgetRegistrazione::controlla() {
    if((*lista)[0]->text()=="")
        throw campo_vuoto();
    else if(r_lia->find((*lista)[0]->text()))
        throw username_esistente();
    else if ((*lista)[3]->text()=="")
        throw campo_vuoto();
    else if(!((*lista)[3]->text().contains(QRegExp("^[a-zA-Z0-9-_.]+@[a-zA-Z0-9-_.]+.\\bcom\\b|\\bit\\b$"))))
        throw errore_email();
    else if((*lista)[3]->text()!=(*lista)[4]->text())
        throw errore_conf_email();
    else if((*lista)[5]->text().size()<8)
        throw errore_pwd();
    else if ((*lista)[5]->text()!=(*lista)[6]->text())
        throw errore_conf_pwd();
    else {
        return true;
    }
}

bool WidgetRegistrazione::conferma_reg() {
    r_lia = new LinQedInAdmin();
    try { return controlla(); }
    catch(campo_vuoto) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","I campi contrassegnati da * non possono essere lasciati vuoti",QMessageBox::Ok,this);
        mb->show();
    }
    catch(username_esistente) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Username già in uso",QMessageBox::Ok,this);
        mb->show();
        resetta();
    }
    catch(errore_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Formato email non corretto",QMessageBox::Ok,this);
        mb->show();
        (*lista)[3]->setText("");
        (*lista)[4]->setText("");
    }
    catch(errore_conf_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Le email non corrispondono",QMessageBox::Ok,this);
        mb->show();
        (*lista)[3]->setText("");
        (*lista)[4]->setText("");
    }
    catch(errore_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","La password deve essere almeno di 8 caratteri",QMessageBox::Ok,this);
        mb->show();
        (*lista)[5]->setText("");
        (*lista)[6]->setText("");
    }
    catch(errore_conf_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Le password non corrispondono",QMessageBox::Ok,this);
        mb->show();
        (*lista)[5]->setText("");
        (*lista)[6]->setText("");
    }
    return false;
}

void WidgetRegistrazione::inserisci_utente() {
    r_lia->insert((*lista)[0]->text(),1,(*lista)[3]->text(),(*lista)[1]->text(),(*lista)[2]->text());
}
