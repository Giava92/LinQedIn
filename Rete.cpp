#include "Rete.h"

Rete::Rete(): net(QList<Username>()) {}

void Rete::add(Username u, const DB& d) {
    if(d.find(u))
        net.append(u);
}

int Rete::remove(Username u) {
    return net.removeAll(u);
}
