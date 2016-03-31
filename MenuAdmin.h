#ifndef MENUADMIN
#define MENUADMIN

#include <QMenuBar>

class MenuAdmin: public QMenuBar {
private:
    QMenu* filemenu;
    QAction* carica;
    QAction* salva;
public:
    MenuAdmin(QWidget* parent =0);
    QMenu* getmenu();
    QAction* getcarica();
    QAction* getsalva();
};

#endif // MENUADMIN

