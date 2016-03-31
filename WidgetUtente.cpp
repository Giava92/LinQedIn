#include "WidgetUtente.h"

WidgetUtente::WidgetUtente(QWidget *parent): QWidget(parent) {
    logout = new QPushButton("logout",parent);
    logout->setFixedWidth(50);
    QIcon* load = new QIcon("carica.png");
    QIcon* save = new QIcon("salva.png");
    carica = new QPushButton(*load,"",parent);
    carica->setFixedSize(30,30);
    carica->setToolTip("Carica");
    salva = new QPushButton(*save,"",parent);
    salva->setFixedSize(30,30);
    salva->setToolTip("Salva");
}

QPushButton* WidgetUtente::getlogout() const {
    return logout;
}

QPushButton* WidgetUtente::getcarica() const {
    return carica;
}

QPushButton* WidgetUtente::getsalva() const {
    return salva;
}

WidgetUtente::~WidgetUtente() {}
