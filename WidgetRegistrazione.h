#ifndef WIDGETREGISTRAZIONE
#define WIDGETREGISTRAZIONE

#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include "LinQedInAdmin.h"

class WidgetRegistrazione: public QWidget {
    Q_OBJECT
private:
    QPushButton* indietro;
    QPushButton* reset;
    QPushButton* conferma;
    QList<QLineEdit*>* lista;
    LinQedInAdmin* r_lia;
public:
    WidgetRegistrazione(QWidget* parent =0);
    QPushButton* getIndietro() const;
    QPushButton* getReset() const;
    QPushButton* getConferma() const;
    QList<QLineEdit*>* getlista() const;
    LinQedInAdmin* getr_lia() const;
    bool controlla();
    bool conferma_reg();
    void inserisci_utente();
    class campo_vuoto {};
    class username_esistente {};
    class errore_email {};
    class errore_conf_email {};
    class errore_pwd {};
    class errore_conf_pwd {};
public slots:
    void resetta();
};

#endif // WIDGETREGISTRAZIONE

