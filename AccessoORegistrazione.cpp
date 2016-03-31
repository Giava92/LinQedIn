#include "AccessoORegistrazione.h"
#include <QGridLayout>

AccessoORegistrazione::AccessoORegistrazione(QWidget* parent): QWidget(parent) {
    linqedin = new QLabel("LinQedIn");
    linqedin->setStyleSheet("font-size: 50px;");
    descr = new QLabel("Accedi con i tuoi dati oppure Registrati",this);
    descr->setFixedHeight(30);
    descr->setStyleSheet("font-size: 20px;");
    descr->setAlignment(Qt::AlignHCenter);
    accedi = new QPushButton("Accedi", this);
    accedi->setFixedWidth(110);
    accedi->setStyleSheet("font-size: 20px;");
    registrati = new QPushButton("Registrati",this);
    registrati->setFixedWidth(110);
    registrati->setStyleSheet("font-size: 20px;");
    setMinimumSize(500,200);
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(linqedin,0,1,1,2,Qt::AlignHCenter);
    gl->addWidget(descr,1,1,1,2,Qt::AlignHCenter);
    gl->setRowMinimumHeight(2,20);
    gl->addWidget(accedi,3,1,Qt::AlignHCenter);
    gl->addWidget(registrati,3,2,Qt::AlignHCenter);
    setLayout(gl);
}

QPushButton* AccessoORegistrazione::getAccedi() const {
    return accedi;
}

QPushButton* AccessoORegistrazione::getRegistrati() const {
    return registrati;
}
