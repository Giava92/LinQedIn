#include "Username.h"

Username::Username() {}

Username::Username(QString s): login(s) {}

bool Username::operator==(const Username& un) const {
    return login == un.login;
}
