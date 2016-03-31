#include "CreazioneUtente.h"
#include <QGridLayout>
#include <QLabel>

CreazioneUtente::CreazioneUtente(QWidget* parent): QWidget(parent) {
    user = new QLineEdit(this);
    tipo = new QComboBox(this);
    QStringList tipi;
    tipi<<"Utente Basic"<<"Utente Business"<<"Utente Executive";
    tipo->addItems(tipi);
    nome = new QLineEdit(this);
    cogn = new QLineEdit(this);
    email = new QLineEdit(this);
    conf_email = new QLineEdit(this);
    paswd = new QLineEdit(this);
    paswd->setEchoMode(QLineEdit::Password);
    conf_paswd  = new QLineEdit(this);
    conf_paswd->setEchoMode(QLineEdit::Password);
    contat = new QTextEdit(this);
    reset = new QPushButton("Reset", this);
    ok = new QPushButton("Ok", this);
    ok->setFixedWidth(80);
    QLabel* lu = new QLabel("Username*:",this);
    QLabel* lt = new QLabel("Tipo:",this);
    QLabel* ln = new QLabel("Nome:",this);
    QLabel* lc = new QLabel("Cognome:",this);
    QLabel* le = new QLabel("Email*:",this);
    QLabel* lce = new QLabel("Conferma Email*:",this);
    QLabel* lp = new QLabel("Password*:",this);
    QLabel* lcp = new QLabel("Conferma Password*:",this);
    QLabel* lct = new QLabel("Contatti:",this);
    QLabel* info = new QLabel("I campi contrassegnati da * sono obbligatori.",this);
    QGridLayout* gr = new QGridLayout;
    gr->addWidget(lu,0,0);
    gr->addWidget(user,0,1);
    gr->addWidget(lt,1,0);
    gr->addWidget(tipo,1,1);
    gr->addWidget(ln,2,0);
    gr->addWidget(nome,2,1);
    gr->addWidget(lc,3,0);
    gr->addWidget(cogn,3,1);
    gr->addWidget(le,4,0);
    gr->addWidget(email,4,1);
    gr->addWidget(lce,5,0);
    gr->addWidget(conf_email,5,1);
    gr->addWidget(lp,6,0);
    gr->addWidget(paswd,6,1);
    gr->addWidget(lcp,7,0);
    gr->addWidget(conf_paswd,7,1);
    gr->addWidget(lct,8,0);
    gr->addWidget(contat,8,1);
    gr->addWidget(info,9,0,1,2,Qt::AlignHCenter);
    gr->addWidget(reset,10,0);
    gr->addWidget(ok,10,1,1,1,Qt::AlignHCenter);
    setLayout(gr);
    tipo->setStyleSheet("selection-background-color: lightgray;");
    QWidget::connect(reset,SIGNAL(clicked()),this,SLOT(resetta()));
}

QLineEdit* CreazioneUtente::getUser() const {
    return user;
}

QComboBox* CreazioneUtente::getTipo() const {
    return tipo;
}

QLineEdit* CreazioneUtente::getNome() const {
    return nome;
}

QLineEdit* CreazioneUtente::getCogn() const {
    return cogn;
}

QLineEdit* CreazioneUtente::getEmail() const {
    return email;
}

QLineEdit* CreazioneUtente::getConfEmail() const {
    return conf_email;
}

QLineEdit* CreazioneUtente::getPaswd() const {
    return paswd;
}

QLineEdit* CreazioneUtente::getConfPaswd() const {
    return conf_paswd;
}

QTextEdit* CreazioneUtente::getContat() const {
    return contat;
}

QPushButton* CreazioneUtente::getOk() const {
    return ok;
}

QPushButton* CreazioneUtente::getReset() const {
    return reset;
}

void CreazioneUtente::resetta() {
    user->setText("");
    tipo->setCurrentIndex(0);
    nome->setText("");
    cogn->setText("");
    email->setText("");
    conf_email->setText("");
    contat->setText("");
    paswd->setText("");
    conf_paswd->setText("");
}
