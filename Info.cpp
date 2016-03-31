#include "Info.h"

Info::Info(QString e, QString n, QString c): email(e), nome(n), cognome(c) {}

QString Info::getNome() const {return nome;}

QString Info::getCognome() const {return cognome;}

QString Info::getEmail() const {return email;}

void Info::setEmail(QString s) {email = s;}

void Info::setNome(QString n) {nome = n;}

void Info::setCognome(QString c) {cognome = c;}
