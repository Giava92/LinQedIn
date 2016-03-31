#ifndef UTENTEEXECUTIVE
#define UTENTEEXECUTIVE

#include "Utente.h"

class UtenteExecutive: public Utente {
public:
    UtenteExecutive(Username);
    ~UtenteExecutive();
    // overriding: ricerca per un utente Executive, funtore di tipo 3
    virtual QTableWidget* userSearch(const DB&,const Username&) const;
    virtual UtenteExecutive* clone() const;
    virtual int getTipo() const;
};

#endif // UTENTEEXECUTIVE

