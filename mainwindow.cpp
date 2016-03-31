#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UtenteBasic.h"
#include "UtenteBusiness.h"
#include "UtenteExecutive.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QToolBar>
#include <typeinfo>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->setMovable(false);
    aor = new AccessoORegistrazione(this);
    setCentralWidget(aor);
    show();
    QWidget::connect(aor->getAccedi(),SIGNAL(clicked()),this,SLOT(scegliutente()));
    QWidget::connect(aor->getRegistrati(),SIGNAL(clicked()),this,SLOT(registrazione()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scegliutente() {
    wsu = new WidgetSceltaUtente(this);
    wsu->setWindowFlags(Qt::Window);
    wsu->setWindowModality(Qt::WindowModal);
    wsu->setWindowTitle("Scegli Utente");
    wsu->show();
    QWidget::connect(wsu->get_ok(),SIGNAL(clicked()),this, SLOT(verifica()));
    QWidget::connect(wsu->get_testo(), SIGNAL(textChanged(QString)),this, SLOT(IdUser(QString)));
    QWidget::connect(wsu->get_password(), SIGNAL(textChanged(QString)), this, SLOT(Password(QString)));
}

void MainWindow::registrazione() {
    delete aor;
    wr = new WidgetRegistrazione(this);
    setCentralWidget(wr);
    setMinimumSize(500,400);
    QWidget::connect(wr->getIndietro(),SIGNAL(clicked()),this,SLOT(tornaindietro()));
    QWidget::connect(wr->getConferma(),SIGNAL(clicked()),this,SLOT(completa_reg()));
}

void MainWindow::tornaindietro() {
    delete wr;
    aor = new AccessoORegistrazione(this);
    setCentralWidget(aor);
    QWidget::connect(aor->getAccedi(),SIGNAL(clicked()),this,SLOT(scegliutente()));
    QWidget::connect(aor->getRegistrati(),SIGNAL(clicked()),this,SLOT(registrazione()));
}

void MainWindow::completa_reg() {
    if(wr->conferma_reg()) {
        wr->inserisci_utente();
        savefile_u();
        savefile_d();
        savefile_r();

        QMessageBox* mb = new QMessageBox(QMessageBox::NoIcon,"LinQedIn","Registrazione effettuata con successo",QMessageBox::Ok,this);
        mb->show();
        tornaindietro();
    }

}

void MainWindow::logout() {
    QPushButton* p = dynamic_cast<QPushButton*>(sender());
    if(p==wu->getlogout()) {
        delete wu;
        delete wu->getlogout();
        delete wu->getcarica();
        delete wu->getsalva();
        delete menuBar();
        ui->mainToolBar->clear();
    }
    aor = new AccessoORegistrazione(this);
    setCentralWidget(aor);
    aor->setMinimumSize(500,200);
    setMinimumSize(600,300);
    QWidget::connect(aor->getAccedi(),SIGNAL(clicked()),this,SLOT(scegliutente()));
    QWidget::connect(aor->getRegistrati(),SIGNAL(clicked()),this,SLOT(registrazione()));
}

void MainWindow::verifica() {
    QFile file("utenti.xml");
    if(file.size()==0){
        file.open(QIODevice::ReadWrite|QIODevice::Text);
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.writeStartElement("Lista");
        xmlWriter.writeStartElement("Utente");
        xmlWriter.writeTextElement("Username","admin");
        xmlWriter.writeTextElement("Password","0f55bbfef6d9256f7fdca250b6533353db915bcf");
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        file.close();
    }
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QXmlStreamReader xmlReader(&file);
    bool usertrovato = false;
    bool trovato = false;
    bool esiste = true;
    while(!trovato && esiste && !xmlReader.atEnd()) {
        if(xmlReader.isStartElement()) {
            if(xmlReader.name() == "Lista")
                xmlReader.readNext();
            else if(xmlReader.name() == "Utente")
                xmlReader.readNext();
            else if(xmlReader.name() == "Username") {
                QString xmlu = xmlReader.readElementText();
                if(user == xmlu)
                   usertrovato = true;
                xmlReader.readNext();
            }
            else if(xmlReader.name() == "Password") {
                QString xmlp = xmlReader.readElementText();
                if(usertrovato && pwd == xmlp)
                    trovato = true;
                else if(usertrovato)
                    esiste = false;
                xmlReader.readNext();
            }
        }
        else
            xmlReader.readNext();
    }
    if(trovato) {
        delete aor;
        if(user == "admin") {
            ma = new MenuAdmin(0);
            ma->setMinimumSize(16,16);
            setMenuBar(ma);
            wu = new WidgetAdmin(this);
            completeadminactions();
        }
        else {
            wu = new WidgetUtenteNormale(user,this);
            setCentralWidget(wu);
        }
        ui->mainToolBar->setMinimumHeight(40);
        ui->mainToolBar->addWidget(wu->getlogout());
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addWidget(wu->getcarica());
        ui->mainToolBar->addWidget(wu->getsalva());
        ui->mainToolBar->addSeparator();
        QWidget::connect(wu->getlogout(),SIGNAL(clicked()),this,SLOT(logout()));
    }
    else {
        user = "";
        wsu = new WidgetSceltaUtente(this);
        wsu->setWindowFlags(Qt::Window);
        wsu->setWindowModality(Qt::WindowModal);
        wsu->setWindowTitle("Scegli Utente");
        QLabel* l = new QLabel("dati errati, prova a reinserirli", wsu);
        delete wsu->layout();
        QGridLayout* grid1 = new QGridLayout;
        grid1->addWidget(l, 1, 1, 1, 1);
        grid1->addWidget(wsu->get_testo(), 2, 1, 1, 2);
        grid1->addWidget(wsu->get_password(), 3, 1, 1, 2);
        grid1->addWidget(wsu->get_reset(), 4, 1, 1, 1);
        grid1->addWidget(wsu->get_ok(), 4, 2, 1, 1);
        wsu->setLayout(grid1);
        wsu->setMinimumSize(280,150);
        wsu->show();
        l->show();
        QWidget::connect(wsu->get_ok(),SIGNAL(clicked()),this, SLOT(verifica()));
        QWidget::connect(wsu->get_testo(), SIGNAL(textChanged(QString)),this, SLOT(IdUser(QString)));
        QWidget::connect(wsu->get_password(), SIGNAL(textChanged(QString)), this, SLOT(Password(QString)));
    }
}

void MainWindow::carica() {
    setMinimumSize(1000,600);
    WidgetAdmin* wa = dynamic_cast<WidgetAdmin*>(wu);
    wa->mostradb();
    wa->getTable()->verticalHeader()->setVisible(false);
    ui->mainToolBar->setMinimumHeight(40);
    ui->mainToolBar->addWidget(wa->getAdd());
    setCentralWidget(wa);
    wa->show();
    wa->getAdd()->show();
}

void MainWindow::salva() {
    wu->save();
}

void MainWindow::completeadminactions() {
    QWidget::connect(ma->getcarica(),SIGNAL(triggered()),this, SLOT(carica()));
    QWidget::connect(wu->getcarica(),SIGNAL(clicked()),this,SLOT(carica()));
    QWidget::connect(ma->getsalva(), SIGNAL(triggered()),this, SLOT(salva()));
    QWidget::connect(wu->getsalva(),SIGNAL(clicked()),this,SLOT(salva()));
}

void MainWindow::IdUser(QString s) {
    user = s;
}

void MainWindow::Password(QString p) {
    QCryptographicHash* ch = new QCryptographicHash(QCryptographicHash::Sha1);
    pwd = (ch->hash(p.toUtf8(), QCryptographicHash::Sha1)).toHex();
}

void MainWindow::savefile_u() {
    QFile file("utenti.xml");
    QFile file1("~utenti.xml");
    file.open(QFile::ReadOnly);
    file1.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file1);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(-1);
    QXmlStreamReader xmlReader(&file);
    while(!xmlReader.atEnd()) {

      if(xmlReader.isStartElement())
        xmlWriter.writeStartElement(xmlReader.name().toString());
      if(xmlReader.isCharacters())
          xmlWriter.writeCharacters(xmlReader.text().toString());

      if(xmlReader.isEndElement()) {
          if(xmlReader.name()=="Lista") {
              xmlWriter.writeStartElement("Utente");
              xmlWriter.writeTextElement("Username",(*(wr->getlista()))[0]->text());
              Password(((*(wr->getlista()))[5]->text()));
              xmlWriter.writeTextElement("Password",pwd);
              xmlWriter.writeEndElement();
          }
        xmlWriter.writeEndElement();
      }

      xmlReader.readNext();
    }
    file.remove();
    file1.rename("utenti.xml");
}

void MainWindow::savefile_d() {
    QFile file("database.xml");
    QFile file1("~database.xml");
    file.open(QFile::ReadOnly);
    file1.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file1);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(-1);
    QXmlStreamReader xmlReader(&file);
    while(!xmlReader.atEnd()) {

      if(xmlReader.isStartElement())
        xmlWriter.writeStartElement(xmlReader.name().toString());
      if(xmlReader.isCharacters())
          xmlWriter.writeCharacters(xmlReader.text().toString());

      if(xmlReader.isEndElement()) {
          if(xmlReader.name()=="Database") {
              xmlWriter.writeStartElement("Utente");
              xmlWriter.writeTextElement("Username",(*(wr->getlista()))[0]->text());
              int n = wr->getr_lia()->find((*(wr->getlista()))[0]->text())->getTipo();
              if(n==1)
                  xmlWriter.writeTextElement("Tipo", "Utente Basic");
              else if (n==2)
                  xmlWriter.writeTextElement("Tipo", "Utente Business");
              else if (n==3)
                  xmlWriter.writeTextElement("Tipo", "Utente Executive");
              xmlWriter.writeStartElement("Profilo");
              if((*(wr->getlista()))[1]->text()!="")
                xmlWriter.writeTextElement("Nome", (*(wr->getlista()))[1]->text());
              if((*(wr->getlista()))[2]->text()!="")
                xmlWriter.writeTextElement("Cognome",(*(wr->getlista()))[2]->text());
              xmlWriter.writeTextElement("Email",(*(wr->getlista()))[3]->text());
              xmlWriter.writeEndElement();
              xmlWriter.writeEndElement();
          }
        xmlWriter.writeEndElement();
      }

      xmlReader.readNext();
    }
    file.remove();
    file1.rename("database.xml");
}

void MainWindow::savefile_r() {
    QFile file("rete.xml");
    QFile file1("~rete.xml");
    file.open(QFile::ReadOnly);
    file1.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file1);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(-1);
    QXmlStreamReader xmlReader(&file);
    while(!xmlReader.atEnd()) {

      if(xmlReader.isStartElement())
        xmlWriter.writeStartElement(xmlReader.name().toString());
      if(xmlReader.isCharacters())
          xmlWriter.writeCharacters(xmlReader.text().toString());

      if(xmlReader.isEndElement()) {
          if(xmlReader.name()=="Reti") {
              xmlWriter.writeStartElement("Utente");
              xmlWriter.writeTextElement("Username",(*(wr->getlista()))[0]->text());
              xmlWriter.writeStartElement("Rete");
              Utente* ut = wr->getr_lia()->find((*(wr->getlista()))[0]->text());
              if(ut->rete) {
                  QList<Username>::const_iterator itnet = ut->rete->net.begin();
                  for( ; itnet != ut->rete->net.end(); ++itnet)
                      xmlWriter.writeTextElement("Contatto", itnet->login);
              }
              xmlWriter.writeEndElement();
              xmlWriter.writeEndElement();
          }
        xmlWriter.writeEndElement();
      }

      xmlReader.readNext();
    }
    file.remove();
    file1.rename("rete.xml");
}
