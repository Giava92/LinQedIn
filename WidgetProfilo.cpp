#include "WidgetProfilo.h"
#include <QHeaderView>
#include <QGridLayout>
#include <QFile>
#include <QCryptographicHash>
#include <QMessageBox>

WidgetProfilo::WidgetProfilo(LinQedInClient* plic, QWidget *parent): QWidget(parent) {
    p_lic = plic;
    pwd = "";
    slabel = new QList<QLabel*>();
    dlabel = new QList<QLabel*>();
    info = new QLabel("Il campo Username non è modificabile.\n"
                      "Per non modificare la password lasciare vuoti i campi Nuova password e Conferma nuova password.");
    sm_e = new QSignalMapper(this);
    slabel->append(new QLabel("Username",this));
    username = new QLabel(p_lic->u->un.login,this);
    slabel->append(new QLabel("Nome",this));
    dlabel->append(new QLabel(p_lic->u->pf.getProfilo()->getNome(),this));
    slabel->append(new QLabel("Cognome",this));
    dlabel->append(new QLabel(p_lic->u->pf.getProfilo()->getCognome(),this));
    slabel->append(new QLabel("Email",this));
    dlabel->append(new QLabel(p_lic->u->pf.getProfilo()->getEmail(),this));
    slabel->append(new QLabel("Contatti",this));
    tcont = new QTableWidget(this);
    tcont->setColumnCount(2);
    tcont->setRowCount(0);
    QList<Username>::const_iterator it = (p_lic->u->rete->net).begin();
    for(; it != ((p_lic->u->rete)->net).end(); ++it) {
        tcont->insertRow(tcont->rowCount());
        tcont->setItem((tcont->rowCount())-1,1,new QTableWidgetItem(it->login));
        tcont->item((tcont->rowCount())-1,1)->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        tcont->setRowHeight(tcont->rowCount()-1,20);
    }
    tcont->setFixedWidth(100);
    tcont->setColumnWidth(1,100);
    tcont->setFixedHeight(tcont->rowCount()*tcont->rowHeight(0)+5);
    tcont->horizontalHeader()->hide();
    tcont->verticalHeader()->hide();
    tcont->hideColumn(0);
    tcont->setShowGrid(false);
    tcont->setStyleSheet("background-color: transparent; border: none");
    modifica = new QPushButton("Modifica",this);
    conferma = new QPushButton("Conferma",this);
    conferma->setFixedWidth(70);
    conferma->setStyleSheet("QPushButton {padding: 5px;background-color:#1E90FF;border-style: outset;"
                            "border-width: 1px;border-radius: 2px; border-color: gray;} "
                            "QPushButton:hover {background-color:#00BFFF} "
                            "QPushButton:pressed {background-color:#4169E1}");
    conferma->setVisible(false);
    modifica->setFixedWidth(70);
    indietro = new QPushButton("Indietro",this);
    indietro->setFixedWidth(70);
    QGridLayout* lp = new QGridLayout;
    leftlayout(lp);
    lp->addWidget(username,1,2);
    for(int n=0;n<dlabel->size();++n)
            lp->addWidget((*dlabel)[n],n+2,2);
    lp->addWidget(tcont,5,2,Qt::AlignLeft);
    lp->addWidget(modifica,7,0,Qt::AlignHCenter);
    lp->addWidget(indietro,7,2,Qt::AlignLeft);
    lp->setColumnMinimumWidth(1,100);
    lp->setRowMinimumHeight(6,90);
    setLayout(lp);
    QWidget::connect(modifica,SIGNAL(clicked()),this,SLOT(iniz_modifica()));
}

QPushButton* WidgetProfilo::getindietro() const {
    return indietro;
}

QPushButton*WidgetProfilo::getmodifica() const {
    return modifica;
}

QPushButton* WidgetProfilo::getconferma() const {
    return conferma;
}

QTableWidget* WidgetProfilo::gettcont() const {
    return tcont;
}

QLabel* WidgetProfilo::getuser() const {
    return username;
}

QLabel* WidgetProfilo::getinfo() const {
    return info;
}

QList<QLabel*>* WidgetProfilo::getslabel() const {
    return slabel;
}

QList<QLabel*>* WidgetProfilo::getdlabel() const {
    return dlabel;
}

QList<QLineEdit*>* WidgetProfilo::getlelabel() const {
    return lelabel;
}

void WidgetProfilo::leftlayout(QGridLayout* gl) {
    for(int n=0;n<slabel->size();++n)
            gl->addWidget((*slabel)[n],n+1,0);
}

void WidgetProfilo::iniz_modifica() {
    lelabel = new QList<QLineEdit*>();
    tcont->showColumn(0);
    tcont->setColumnWidth(0,20);
    tcont->setFixedWidth(130);
    for(int x=0;x<tcont->rowCount();++x) {
        QPushButton* rem = new QPushButton("x",tcont);
        rem->setStyleSheet("QPushButton {color: red; font: bold; border-radius: 5px; "
                           "border-style: outset;border-width: 1px; border-color: gray;} "
                           "QPushButton:hover {background-color:#F5F5F5} "
                           "QPushButton:pressed {background-color:#A9A9A9}");
        rem->setToolTip("<font style =\"font:normal; background-color: white; "
                        "color:black\">rimuovi Utente</font>");
        rem->setFixedWidth(18);
        rem->setFixedHeight(18);
        tcont->setCellWidget(x, 0, rem);
        QWidget::connect(rem,SIGNAL(clicked()),sm_e,SLOT(map()));
        sm_e->setMapping(rem, x);
    }
    QWidget::connect(sm_e,SIGNAL(mapped(int)),this,SLOT(gestelimina(int)));
    modifica->setVisible(false);
    indietro->setEnabled(false);
    for(int i=0;i<dlabel->size()+2;++i) {
        if(i==dlabel->size()||i==dlabel->size()+1) {
            lelabel->append(new QLineEdit("",this));
            (*lelabel)[lelabel->size()-1]->setEchoMode(QLineEdit::Password);
        }
        else {
        lelabel->append(new QLineEdit(((*dlabel)[i])->text(),this)); 
        delete (*dlabel)[i];
        }
        (*lelabel)[i]->setFixedWidth(150);
    }
    email = (*lelabel)[lelabel->size()-3]->text();
    delete dlabel;
    slabel->insert(slabel->size()-1,new QLabel("Nuova password",this));
    slabel->insert(slabel->size()-1,new QLabel("Conferma nuova password",this));
    info->setVisible(true);
    if(layout())
        delete layout();
    QGridLayout* nlp = new QGridLayout;
    leftlayout(nlp);
    nlp->addWidget(username,1,2);
    for(int n=0;n<lelabel->size();++n)
            nlp->addWidget((*lelabel)[n],n+2,2);
    nlp->addWidget(tcont,slabel->size(),2,Qt::AlignLeft);
    nlp->addWidget(info,slabel->size()+1,0,1,3,Qt::AlignHCenter);
    conferma->setVisible(true);
    nlp->addWidget(conferma,slabel->size()+2,0,Qt::AlignHCenter);
    nlp->addWidget(indietro,slabel->size()+2,2,Qt::AlignLeft);
    nlp->setColumnMinimumWidth(1,100);
    nlp->setRowMinimumHeight(slabel->size()+1,90);
    setLayout(nlp);
    QWidget::connect(conferma,SIGNAL(clicked()),this,SLOT(comp_modifica()));
}

void WidgetProfilo::comp_modifica() {
    bool problema=true;
    try {problema=controlla();}
    catch(email_vuota) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","L'email non può essere vuota",QMessageBox::Ok,this);
        mb->show();
        (*lelabel)[lelabel->size()-3]->setText(email);
    }
    catch(errore_email) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Formato email non corretto",QMessageBox::Ok,this);
        mb->show();
        (*lelabel)[lelabel->size()-3]->setText(email);
    }
    catch(errore_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","La password deve essere almeno di 8 caratteri",QMessageBox::Ok,this);
        mb->show();
        (*lelabel)[lelabel->size()-2]->setText("");
        (*lelabel)[lelabel->size()-1]->setText("");
    }
    catch(errore_conf_pwd) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Le password non corrispondono",QMessageBox::Ok,this);
        mb->show();
        (*lelabel)[lelabel->size()-2]->setText("");
        (*lelabel)[lelabel->size()-1]->setText("");
    }
    if(!problema) {
    tcont->hideColumn(0);
    tcont->setFixedWidth(100);
    tcont->setColumnWidth(1,100);
    delete (*slabel)[slabel->size()-3];
    delete (*slabel)[slabel->size()-2];
    slabel->removeAt(slabel->size()-2);
    slabel->removeAt(slabel->size()-2);
    dlabel = new QList<QLabel*>();
    conferma->setVisible(false);
    info->setVisible(false);
    indietro->setEnabled(true);
    for(int i=0;i<lelabel->size();i++) {
        dlabel->append(new QLabel(((*lelabel)[i])->text(),this));
        delete (*lelabel)[i];
    }
    delete lelabel;
    modifica->setVisible(true);
    if(layout())
        delete layout();
    QGridLayout* nlp = new QGridLayout;
    leftlayout(nlp);
    nlp->addWidget(username,1,2);
    for(int n=0;n<dlabel->size();++n)
            nlp->addWidget((*dlabel)[n],n+2,2);
    nlp->addWidget(tcont,5,2,Qt::AlignLeft);
    nlp->addWidget(info,6,0,1,3,Qt::AlignHCenter);
    nlp->addWidget(modifica,7,0,Qt::AlignHCenter);
    nlp->addWidget(indietro,7,2,Qt::AlignLeft);
    nlp->setColumnMinimumWidth(1,100);
    nlp->setRowMinimumHeight(6,90);
    setLayout(nlp);
    QWidget::connect(modifica,SIGNAL(clicked()),this,SLOT(iniz_modifica()));
    }
}

void WidgetProfilo::gestelimina(int e) {
    p_lic->removeRete(tcont->item(e,tcont->columnCount()-1)->text());
    tcont->removeRow(e);    
    delete sm_e;
    sm_e = new QSignalMapper(this);
    for(int i=0;i<tcont->rowCount();++i) {
        QWidget* order_e = tcont->cellWidget(i,0);
        QWidget::connect(order_e,SIGNAL(clicked()),sm_e,SLOT(map()));
        sm_e->setMapping(order_e, i);
    }
}

QString WidgetProfilo::getpwd() const {
    return pwd;
}

bool WidgetProfilo::controlla() {
    if((*lelabel)[lelabel->size()-3]->text()=="")
        throw email_vuota();
    else if(!((*lelabel)[lelabel->size()-3]->text().contains(QRegExp("^[a-zA-Z0-9-_.]+@[a-zA-Z0-9-_.]+.\\bcom\\b|\\bit\\b$"))))
        throw errore_email();
    else if((*lelabel)[lelabel->size()-2]->text()!="") {
        if((*lelabel)[lelabel->size()-2]->text().size()<8)
            throw errore_pwd();
        else if((*lelabel)[lelabel->size()-2]->text()==(*lelabel)[lelabel->size()-1]->text()) {
            pwd = (*lelabel)[lelabel->size()-2]->text();
            QCryptographicHash* ch = new QCryptographicHash(QCryptographicHash::Sha1);
            pwd = (ch->hash(pwd.toUtf8(), QCryptographicHash::Sha1)).toHex();
            delete (*lelabel)[lelabel->size()-2];
            delete (*lelabel)[lelabel->size()-1];
            lelabel->removeAt(lelabel->size()-1);
            lelabel->removeAt(lelabel->size()-1);
            return false;
        }
        else
            throw errore_conf_pwd();
    }
    else if((*lelabel)[lelabel->size()-1]->text()!="")
        throw errore_conf_pwd();
    else {
        delete (*lelabel)[lelabel->size()-2];
        delete (*lelabel)[lelabel->size()-1];
        lelabel->removeAt(lelabel->size()-1);
        lelabel->removeAt(lelabel->size()-1);
        return false;
    }
}
