#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "AccessoORegistrazione.h"
#include "WidgetSceltaUtente.h"
#include "MenuAdmin.h"
#include "LinQedInAdmin.h"
#include "WidgetAdmin.h"
#include "WidgetUtenteNormale.h"
#include "WidgetUtente.h"
#include "WidgetRegistrazione.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void completeadminactions();
public slots:
    void IdUser(QString);
    void Password(QString);
    void scegliutente();
    void registrazione();
    void tornaindietro();
    void completa_reg();
    void logout();
    void verifica();
    void carica();
    void salva();
    void savefile_u();
    void savefile_d();
    void savefile_r();
private:
    Ui::MainWindow* ui;
    AccessoORegistrazione* aor;
    WidgetSceltaUtente* wsu;
    WidgetRegistrazione* wr;
    MenuAdmin* ma;
    WidgetUtente* wu;
    QString user;
    QString pwd;
};

#endif // MAINWINDOW_H
