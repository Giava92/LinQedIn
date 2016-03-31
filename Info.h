#ifndef INFO_H
#define INFO_H

#include <QString>

class Info {
private:
    QString email;
    QString nome;
    QString cognome;
public:
    Info(QString e="d", QString n="e", QString c="f");
    QString getNome() const;
    QString getCognome() const;
    QString getEmail() const;
    void setEmail(QString);
    void setNome(QString);
    void setCognome(QString);
};

#endif // INFO_H
