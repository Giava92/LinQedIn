#ifndef WIDGETRICERCA
#define WIDGETRICERCA

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSignalMapper>
#include "LinQedInClient.h"

class WidgetRicerca: public QWidget {
    Q_OBJECT
private:
    QLineEdit* searchbar;
    QPushButton* avviaricerca;
    QLabel* info;
    QPushButton* indietro;
    LinQedInClient* r_lic;
    QString ut_ric;
    QSignalMapper* sm_a;
    QTableWidget* tbr;
public:
    WidgetRicerca(LinQedInClient*, QWidget* parent =0);
    QLineEdit*  getsearch() const;
    QPushButton* getricerca() const;
    QLabel* getinfo() const;
    QPushButton* getindietro() const;
    QSignalMapper* getsm_a() const;
    QTableWidget* gettbr() const;
public slots:
    void comp_ric();
    void searcheduser(QString);
    void aggiungiut(int);
};

#endif // WIDGETRICERCA

