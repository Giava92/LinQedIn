#include "WidgetUtenteNormale.h"
#include <QGridLayout>
#include <QIcon>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>

WidgetUtenteNormale::WidgetUtenteNormale(QString s, QWidget *parent): WidgetUtente(parent) {
    pwd = "";
    getcarica()->setEnabled(false);
    nutente = s;
    benvenuto = new QLabel("Sei connesso come " + nutente,this);
    benvenuto->setFixedHeight(30);
    profilo = new QPushButton("Profilo", this);
    profilo->setFixedWidth(50);
    cerca = new QPushButton("Cerca",this);
    cerca->setFixedWidth(50);
    benvenuto->setStyleSheet("font-size: 16px; font: bold");
    lic = new LinQedInClient(nutente);
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(benvenuto,2,0,2,2,Qt::AlignCenter);
    gl->addWidget(profilo,3,0,2,1,Qt::AlignHCenter);
    gl->addWidget(cerca,3,1,2,1,Qt::AlignHCenter);
    setLayout(gl);
    QWidget::connect(profilo,SIGNAL(clicked()),this,SLOT(mostraprofilo()));
    QWidget::connect(cerca,SIGNAL(clicked()),this,SLOT(mostraricerca()));
    QWidget::connect(getsalva(),SIGNAL(clicked()),this,SLOT(save()));
}

QPushButton* WidgetUtenteNormale::getcerca() const {
    return cerca;
}

QPushButton* WidgetUtenteNormale::getprofilo() const {
    return profilo;
}

QLabel* WidgetUtenteNormale::getbenvenuto() const {
    return benvenuto;
}

void WidgetUtenteNormale::mostraprofilo() {
    delete benvenuto;
    delete profilo;
    delete cerca;
    wp = new WidgetProfilo(lic,this);
    if(layout())
        delete layout();
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(wp,1,1);
    setLayout(gl);
    QWidget::connect(wp->getindietro(),SIGNAL(clicked()),this,SLOT(tornaindietro()));
}

void WidgetUtenteNormale::mostraricerca() {
    delete benvenuto;
    delete profilo;
    delete cerca;
    wr = new WidgetRicerca(lic, this);
    if(layout())
        delete layout();
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(wr,1,1);
    setLayout(gl);
    QWidget::connect(wr->getindietro(),SIGNAL(clicked()),this,SLOT(tornaindietro()));
}

void WidgetUtenteNormale::tornaindietro() {
    delete sender()->parent();
    benvenuto = new QLabel("Sei connesso come " + nutente,this);
    benvenuto->setFixedHeight(30);
    profilo = new QPushButton("Profilo", this);
    profilo->setFixedWidth(50);
    cerca = new QPushButton("Cerca",this);
    cerca->setFixedWidth(50);
    benvenuto->setStyleSheet("font-size: 16px; font: bold");
    if(layout())
        delete layout();
    QGridLayout* gl = new QGridLayout;
    gl->addWidget(benvenuto,2,0,2,2,Qt::AlignCenter);
    gl->addWidget(profilo,3,0,2,1,Qt::AlignHCenter);
    gl->addWidget(cerca,3,1,2,1,Qt::AlignHCenter);
    setLayout(gl);
    QWidget::connect(profilo,SIGNAL(clicked()),this,SLOT(mostraprofilo()));
    QWidget::connect(cerca,SIGNAL(clicked()),this,SLOT(mostraricerca()));
}

void WidgetUtenteNormale::save() {
    lic->save();
    if(wp)
        recuperapwd();
    if(pwd !="")
        save_pwd();
    QMessageBox* mb = new QMessageBox(QMessageBox::Information,"LinQedIn","Salvataggio completato",QMessageBox::Ok,this);
    mb->show();
}

void WidgetUtenteNormale::recuperapwd() {
    pwd = wp->getpwd();
}

void WidgetUtenteNormale::save_pwd() {
    QFile file("utenti.xml");
    QFile file1("~utenti.xml");
    file.open(QIODevice::ReadOnly);
    file1.open(QIODevice::WriteOnly);
    QXmlStreamReader xmlReader(&file);
    QXmlStreamWriter xmlWriter(&file1);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(-1);
    while(!xmlReader.atEnd()) {
        if(xmlReader.isStartElement())
            xmlWriter.writeStartElement(xmlReader.name().toString());
        if(xmlReader.isCharacters()) {
            xmlWriter.writeCharacters(xmlReader.text().toString());
            if(xmlReader.text()==nutente) {
                xmlWriter.writeEndElement();
                xmlWriter.writeTextElement("Password",pwd);
                xmlWriter.writeEndElement();
                while(!xmlReader.isEndElement() || xmlReader.name()!="Utente")
                    xmlReader.readNext();
                xmlReader.readNext();
            }
        }
        if(xmlReader.isEndElement())
            xmlWriter.writeEndElement();
        xmlReader.readNext();
    }
    file.remove();
    file1.rename("utenti.xml");
}
