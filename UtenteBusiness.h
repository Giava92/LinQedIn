#ifndef UTENTEBUSINESS
#define UTENTEBUSINESS

#include "Utente.h"

class UtenteBusiness: public Utente {
public:
    UtenteBusiness(Username);
    ~UtenteBusiness();
    // overriding: ricerca per un utente Business, funtore di tipo 2
    virtual QTableWidget* userSearch(const DB&,const Username&) const;
    virtual UtenteBusiness* clone() const;
    virtual int getTipo() const;
};

#endif // UTENTEBUSINESS

