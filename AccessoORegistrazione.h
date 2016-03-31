#ifndef ACCESSOOREGISTRAZIONE
#define ACCESSOOREGISTRAZIONE

#include <QPushButton>
#include <QLabel>

class AccessoORegistrazione: public QWidget {
private:
    QLabel* linqedin;
    QLabel* descr;
    QPushButton* accedi;
    QPushButton* registrati;
public:
    AccessoORegistrazione(QWidget* parent =0);
    QPushButton* getAccedi() const;
    QPushButton* getRegistrati() const;
};

#endif // ACCESSOOREGISTRAZIONE

