#include "MenuAdmin.h"

MenuAdmin::MenuAdmin(QWidget* parent): QMenuBar(parent) {
    filemenu = addMenu(tr("File"));
    carica = new QAction(tr("Carica"),this);
    salva = new QAction(tr("Salva"), this);
    filemenu->addAction(carica);
    filemenu->addAction(salva);
}

QMenu* MenuAdmin::getmenu() {
    return filemenu;
}

QAction* MenuAdmin::getcarica() {
    return carica;
}

QAction* MenuAdmin::getsalva() {
    return salva;
}
