#ifndef WIDGETUTENTENORMALE
#define WIDGETUTENTENORMALE

#include "WidgetUtente.h"
#include "LinQedInClient.h"
#include "WidgetProfilo.h"
#include "WidgetRicerca.h"
#include <QPushButton>
#include <QLabel>

class WidgetUtenteNormale: public WidgetUtente {
    Q_OBJECT
private:
    QPushButton* cerca;
    QPushButton* profilo;
    QLabel* benvenuto;
    LinQedInClient* lic;
    QString nutente;
    QString pwd;
    WidgetProfilo* wp;
    WidgetRicerca* wr;
public:
    WidgetUtenteNormale(QString, QWidget* parent=0);
    QPushButton* getprofilo() const;
    QLabel* getbenvenuto() const;
    QPushButton* getcerca() const;
    virtual void save();
    void recuperapwd();
    void save_pwd();
public slots:
    void mostraprofilo();
    void mostraricerca();
    void tornaindietro();

};

#endif // WIDGETUTENTENORMALE

