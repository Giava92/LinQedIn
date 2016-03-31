#ifndef UTENTEBASIC
#define UTENTEBASIC

#include "Utente.h"

class UtenteBasic: public Utente {
public:
    UtenteBasic(Username);
    ~UtenteBasic();
    // overriding: ricerca per un utente Basic, funtore di tipo 1
    virtual QTableWidget* userSearch(const DB&,const Username&) const;
    virtual UtenteBasic* clone() const;
    virtual int getTipo() const;
};

#endif // UTENTEBASIC

