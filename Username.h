#ifndef USERNAME_H
#define USERNAME_H

#include <QString>


class Username {
public:
    QString login;
    Username();
    Username(QString);
    bool operator==(const Username&) const;
};

#endif // USERNAME_H
