#include "Profilo.h"

Profilo::Profilo(QString e, QString n, QString c) {
   f = new Info(e, n, c);
}

Profilo::Profilo(Info* inf): f(inf) {}

Profilo& Profilo::operator = (const Profilo& p) {
    f =p.f;
    return *this;
}

void Profilo::modificaProfilo(QString e, QString n, QString c) {
    f->setEmail(e);
    if(!n.isEmpty()) {
        f->setNome(n);
        if(!c.isEmpty())
            f->setCognome(c);
    }
}

Info* Profilo::getProfilo() const {
    return f;
}

Profilo::~Profilo() {
    if(f != 0)
        delete f;
}
