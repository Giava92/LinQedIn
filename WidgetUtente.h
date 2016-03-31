#ifndef WIDGETUTENTE
#define WIDGETUTENTE

#include <QWidget>
#include <QPushButton>

class WidgetUtente: public QWidget {
    Q_OBJECT
private:
    QPushButton* logout;
    QPushButton* carica;
    QPushButton* salva;
public:
    WidgetUtente(QWidget* parent =0);
    QPushButton* getlogout() const;
    QPushButton* getcarica() const;
    QPushButton* getsalva() const;
    virtual ~WidgetUtente();
public slots:
    virtual void save() =0;
};

#endif // WIDGETUTENTE
