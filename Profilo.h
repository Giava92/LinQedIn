#ifndef PROFILO_H
#define PROFILO_H

#include "Info.h"

class Profilo {
private:
    Info* f;
public:
    Profilo(QString e="a", QString n="Tizio", QString c="Anonimo");
    Profilo(Info*);
    void modificaProfilo(QString e, QString n="", QString c="");
    Info* getProfilo() const;
    Profilo& operator= (const Profilo&);
    ~Profilo();
};

#endif // PROFILO_H
