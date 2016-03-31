#ifndef WIDGETADMIN
#define WIDGETADMIN

#include "WidgetUtente.h"
#include "CreazioneUtente.h"
#include "LinQedInAdmin.h"
#include <QTableWidget>
#include <QPushButton>
#include <QSignalMapper>

class WidgetAdmin: public WidgetUtente {
    Q_OBJECT
private:
    QTableWidget* tw;
    QPushButton* addut;
    QSignalMapper* sm_r;
    QSignalMapper* sm_m;
    QSignalMapper* sm_l;
    QSignalMapper* sm_c;
    CreazioneUtente* cu;
    LinQedInAdmin* lia;
    QString tipo;
    QString email;
public:
    WidgetAdmin(QWidget* parent =0);
    void addriga();
    QPushButton* getAdd() const;
    QTableWidget* getTable() const;
    QSignalMapper* getSm_r() const;
    QSignalMapper* getSm_m() const;
    QSignalMapper* getSm_l() const;
    QSignalMapper* getSm_c() const;
    void mostradb();
    bool controlla_inserisci();
    bool controlla_modifica(int);
    void adjustsm();
    virtual void save();
    class campo_vuoto {};
    class username_esistente {};
    class errore_email {};
    class errore_conf_email {};
    class errore_contatti {};
    class errore_pwd {};
    class errore_conf_pwd {};
public slots:
    void enableadd();
    void removeriga(int);
    void modriga(int);
    void conferma(int);
    void addutente();
    void completaadd();
};

#endif // WIDGETADMIN

