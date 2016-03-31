#include "WidgetRicerca.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QMessageBox>

WidgetRicerca::WidgetRicerca(LinQedInClient* rlic, QWidget* parent): QWidget(parent) {
    r_lic = rlic;
    info = new QLabel("Inserisci l'userame della persona che vuoi cercare", this);
    QIcon* lente = new QIcon("lente.png");
    searchbar = new QLineEdit(this);
    searchbar->setFixedWidth(120);
    avviaricerca = new QPushButton(*lente,"",this);
    avviaricerca->setFixedSize(30,27);
    indietro = new QPushButton("Indietro",this);
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(info,1,0,1,5,Qt::AlignCenter);
    gl->addWidget(searchbar,3,1,1,2,Qt::AlignRight);
    gl->addWidget(avviaricerca,3,3,Qt::AlignLeft);
    gl->addWidget(indietro,5,4,Qt::AlignHCenter);
    gl->setRowMinimumHeight(2,20);
    gl->setRowMinimumHeight(4,20);
    setLayout(gl);
    QWidget::connect(searchbar,SIGNAL(returnPressed()),avviaricerca,SIGNAL(clicked()));
    QWidget::connect(avviaricerca,SIGNAL(clicked()),this, SLOT(comp_ric()));
    QWidget::connect(searchbar, SIGNAL(textChanged(QString)),this, SLOT(searcheduser(QString)));
}

QLineEdit* WidgetRicerca::getsearch() const {
    return searchbar;
}

QPushButton* WidgetRicerca::getricerca() const {
    return avviaricerca;
}

QLabel* WidgetRicerca::getinfo() const {
    return info;
}

QPushButton* WidgetRicerca::getindietro() const {
    return indietro;
}

QSignalMapper* WidgetRicerca::getsm_a() const {
    return sm_a;
}

QTableWidget* WidgetRicerca::gettbr() const {
    return tbr;
}

void WidgetRicerca::searcheduser(QString s) {
    ut_ric = s;
}

void WidgetRicerca::comp_ric() {
    try {tbr = r_lic->ricerca(ut_ric);}
    catch(Utente::utente_non_trovato) {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Errore","Nessun utente corrispondente",QMessageBox::Ok,this);
        mb->show();
        tbr = 0;
    }
    if(tbr) {
        this->close();
        sm_a = new QSignalMapper(this);
        tbr->insertColumn(tbr->columnCount());
        tbr->setHorizontalHeaderItem(tbr->columnCount()-1,new QTableWidgetItem(""));
        for(int r=0;r<tbr->rowCount();++r) {
            QPushButton* agg = new QPushButton("Aggiungi",tbr);
            tbr->setCellWidget(r, tbr->columnCount()-1, agg);
            if(r_lic->u->rete->net.contains(tbr->item(r,0)->text()))
                tbr->cellWidget(r,tbr->columnCount()-1)->setEnabled(false);
            QWidget::connect(agg,SIGNAL(clicked()),sm_a,SLOT(map()));
            sm_a->setMapping(agg,r);
        }
        QWidget::connect(sm_a,SIGNAL(mapped(int)),this,SLOT(aggiungiut(int)));
        tbr->setParent(this);
        delete info;
        delete searchbar;
        delete avviaricerca;
        if(layout())
            delete layout();
        QGridLayout* gl = new QGridLayout;
        gl->addWidget(tbr,1,1,Qt::AlignHCenter);
        gl->addWidget(indietro,2,1,Qt::AlignRight);
        setLayout(gl);
        tbr->show();
        show();
    }
}

void WidgetRicerca::aggiungiut(int u) {
    tbr->cellWidget(u,tbr->columnCount()-1)->setEnabled(false);
    r_lic->insertRete(tbr->item(u,0)->text());
    QMessageBox* msg = new QMessageBox(this);
    msg->setWindowTitle("LinQedIn");
    msg->setText("Utente aggiunto ai propri contatti");
    msg->show();

}
