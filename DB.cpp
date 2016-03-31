#include "DB.h"
#include "UtenteBasic.h"
#include "UtenteBusiness.h"
#include "UtenteExecutive.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <typeinfo>
#include <QString>

Utente* DB::find(Username un) const {
    QList<SmartUtente>::const_iterator it = db.begin();
    for( ; it != db.end(); ++it)
        if(it->u->un == un)
            return it->u->clone();
    return 0;
}

void DB::insert(Username u, int i,QString e,QString n,QString c) {
    Utente* ut;
    switch (i) {
    case 1:
        ut = new UtenteBasic(u);
        break;
    case 2:
        ut = new UtenteBusiness(u);
        break;
    case 3:
        ut = new UtenteExecutive(u);
        break;
    default:
        ut = new UtenteBasic(u);
    }
    ut->pf.modificaProfilo(e,n,c);
    SmartUtente su(ut);
    db.append(su);
}

void DB::save() const {
    QFile file("database.xml");
    QFile file1("~database.xml");
    QFile file_r("rete.xml");
    QFile file_r1("~rete.xml");
    file1.open(QIODevice::WriteOnly);
    file_r1.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriterDatabase(&file1);
    QXmlStreamWriter xmlWriterRete(&file_r1);
    xmlWriterDatabase.setAutoFormatting(true);
    xmlWriterDatabase.setAutoFormattingIndent(-1);
    xmlWriterDatabase.writeStartElement("Database");
    xmlWriterRete.setAutoFormatting(true);
    xmlWriterRete.setAutoFormattingIndent(-1);
    xmlWriterRete.writeStartElement("Reti");
    QList<SmartUtente>::const_iterator it = db.begin();
    for( ; it != db.end(); ++it) {
          xmlWriterDatabase.writeStartElement("Utente");
          xmlWriterDatabase.writeTextElement("Username", it->u->un.login);
          if(it->u->getTipo() == 1)
              xmlWriterDatabase.writeTextElement("Tipo", "Utente Basic");
          else if(it->u->getTipo() == 2)
              xmlWriterDatabase.writeTextElement("Tipo", "Utente Business");
          else if(it->u->getTipo() == 3)
              xmlWriterDatabase.writeTextElement("Tipo", "Utente Executive");
          xmlWriterDatabase.writeStartElement("Profilo");
          xmlWriterDatabase.writeTextElement("Nome", it->u->pf.getProfilo()->getNome());
          xmlWriterDatabase.writeTextElement("Cognome", it->u->pf.getProfilo()->getCognome());
          xmlWriterDatabase.writeTextElement("Email", it->u->pf.getProfilo()->getEmail());
          xmlWriterDatabase.writeEndElement();
          xmlWriterDatabase.writeEndElement();
          xmlWriterRete.writeStartElement("Utente");
          xmlWriterRete.writeTextElement("Username", it->u->un.login);
          xmlWriterRete.writeStartElement("Rete");
          QList<Username>::const_iterator itnet = it->u->rete->net.begin();
          for( ; itnet != it->u->rete->net.end(); ++itnet)
              xmlWriterRete.writeTextElement("Contatto", itnet->login);
          xmlWriterRete.writeEndElement();
          xmlWriterRete.writeEndElement();
    }
    xmlWriterDatabase.writeEndElement();
    xmlWriterRete.writeEndElement();
    file1.close();
    file_r1.close();
    file.remove();
    file1.rename("database.xml");
    file_r.remove();
    file_r1.rename("rete.xml");
}

void DB::load() {
    QFile file("database.xml");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QXmlStreamReader xmlReader(&file);
    QString u="", n="", c="", e="", t="", ct="";
    int ut;
    while(!xmlReader.atEnd()) {
        if(xmlReader.isStartElement()) {
            if(xmlReader.name() == "Database")
                xmlReader.readNext();
            else if(xmlReader.name() == "Utente")
                xmlReader.readNext();
            else if(xmlReader.name() == "Username")
                u = xmlReader.readElementText().replace("&#60;","<");
            else if(xmlReader.name() == "Tipo") {
                t = xmlReader.readElementText();
                if(t == "Utente Basic")
                    ut = 1;
                else if(t == "Utente Business")
                    ut = 2;
                else if(t == "Utente Executive")
                    ut = 3;
            }
            else if(xmlReader.name() == "Profilo")
                xmlReader.readNext();
            else if(xmlReader.name() == "Nome")
                n = xmlReader.readElementText();
            else if(xmlReader.name() == "Cognome")
                c = xmlReader.readElementText();
            else if(xmlReader.name() == "Email"){
                e = xmlReader.readElementText();
                insert(u,ut,e,n,c);
                n=""; c="";
                xmlReader.readNext();
            }
        }
        else
            xmlReader.readNext();
    }
    QFile file_r("rete.xml");
    file_r.open(QIODevice::ReadOnly);
    xmlReader.setDevice(&file_r);
    u = "";
    QList<SmartUtente>::const_iterator it = db.begin();
    while(it!=db.end() && !xmlReader.atEnd()) {
        if(xmlReader.isStartElement()) {
            if(xmlReader.name() == "Reti")
                xmlReader.readNext();
            else if(xmlReader.name() == "Utente")
                xmlReader.readNext();
            else if(xmlReader.name() == "Username") {
                if(u != "")
                    ++it;
                u = xmlReader.readElementText();
            }
            else if(xmlReader.name() == "Rete")
                xmlReader.readNext();
            else if(xmlReader.name() == "Contatto") {
                ct = xmlReader.readElementText();
                Username us(ct);
                if(typeid(*(it->u)) == typeid(UtenteBasic)) {
                    UtenteBasic* ub = static_cast<UtenteBasic*>(it->u);
                    if(u == ub->un.login)
                        it->u->rete->add(us, *this);
                }
                else if(typeid(*(it->u)) == typeid(UtenteBusiness)) {
                    UtenteBusiness* ub = static_cast<UtenteBusiness*>(it->u);
                    if(u == ub->un.login)
                        it->u->rete->add(us, *this);
                }
                else if(typeid(*(it->u)) == typeid(UtenteExecutive)) {
                    UtenteExecutive* ub = static_cast<UtenteExecutive*>(it->u);
                    if(u == ub->un.login)
                        it->u->rete->add(us, *this);
                }
            }
        }
        else
            xmlReader.readNext();
    }
}
