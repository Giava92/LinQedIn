#ifndef WIDGETSCELTAUTENTE
#define WIDGETSCELTAUTENTE

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class WidgetSceltaUtente: public QWidget {
    Q_OBJECT
private:
    QLineEdit* testo;
    QLineEdit* password;
    QPushButton* ok;
    QPushButton* reset;
public:
    WidgetSceltaUtente(QWidget* parent =0);
    QLineEdit* get_testo() const;
    QLineEdit* get_password() const;
    QPushButton* get_ok() const;
    QPushButton* get_reset() const;
public slots:
    void resetta();
};

#endif // WIDGETSCELTAUTENTE

