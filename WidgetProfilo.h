#ifndef WIDGETPROFILO
#define WIDGETPROFILO

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QSignalMapper>
#include "LinQedInClient.h"

class WidgetProfilo: public QWidget {
    Q_OBJECT
private:
    QPushButton* indietro;
    QPushButton* modifica;
    QPushButton* conferma;
    QTableWidget* tcont;
    QLabel* username;
    QLabel* info;
    QList<QLabel*>* slabel;
    QList<QLabel*>* dlabel;
    QList<QLineEdit*>* lelabel;
    QSignalMapper* sm_e;
    QString pwd;
    QString email;
    LinQedInClient* p_lic;
public:
    WidgetProfilo(LinQedInClient*, QWidget* parent =0);
    QPushButton* getindietro() const;
    QPushButton* getmodifica() const;
    QPushButton* getconferma() const;
    QTableWidget* gettcont() const;
    QLabel* getuser() const;
    QLabel*  getinfo() const;
    QList<QLabel*>* getslabel() const;
    QList<QLabel*>* getdlabel() const;
    QList<QLineEdit*>* getlelabel() const;
    QString getpwd() const;
    void leftlayout(QGridLayout*);
    bool controlla();
    class email_vuota {};
    class errore_email {};
    class errore_pwd {};
    class errore_conf_pwd {};
public slots:
    void iniz_modifica();
    void comp_modifica();
    void gestelimina(int);
};

#endif // WIDGETPROFILO

