#include "WidgetSceltaUtente.h"
#include <QGridLayout>

WidgetSceltaUtente::WidgetSceltaUtente(QWidget* parent): QWidget(parent) {
    testo = new QLineEdit("Username",this);
    password = new QLineEdit("password", this);
    password->setEchoMode(QLineEdit::Password);
    ok = new QPushButton(tr("Ok"), this);
    //ok->setFixedWidth(50);
    reset = new QPushButton(tr("reset"), this);
    //reset->setFixedWidth(50);
    QGridLayout* grid = new QGridLayout;
    grid->addWidget(testo, 1, 1, 1, 2);
    grid->addWidget(password, 2, 1, 1, 2);
    grid->addWidget(reset, 3, 1, 1, 1);
    grid->addWidget(ok, 3, 2, 1, 1);
    setLayout(grid);
    testo->selectAll();
    setMinimumSize(280,200);
    QWidget::connect(ok,SIGNAL(clicked()),this,SLOT(close()));
    QWidget::connect(reset,SIGNAL(clicked()),this,SLOT(resetta()));
    QWidget::connect(testo,SIGNAL(returnPressed()),ok,SIGNAL(clicked()));
    QWidget::connect(password,SIGNAL(returnPressed()),ok,SIGNAL(clicked()));
}

QLineEdit* WidgetSceltaUtente::get_testo() const {
    return testo;
}

QLineEdit* WidgetSceltaUtente::get_password() const {
    return password;
}

QPushButton* WidgetSceltaUtente::get_ok() const {
    return ok;
}

QPushButton* WidgetSceltaUtente::get_reset() const {
    return reset;
}

void WidgetSceltaUtente::resetta() {
    testo->setText("Username");
    testo->selectAll();
    testo->setFocus();
    password->setText("password");
}
