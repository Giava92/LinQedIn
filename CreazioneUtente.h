#ifndef CREAZIONEUTENTE
#define CREAZIONEUTENTE

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>

class CreazioneUtente: public QWidget {
    Q_OBJECT
private:
    QLineEdit* user;
    QComboBox* tipo;
    QLineEdit* nome;
    QLineEdit* cogn;
    QLineEdit* email;
    QLineEdit* conf_email;
    QTextEdit* contat;
    QLineEdit* paswd;
    QLineEdit* conf_paswd;
    QPushButton* ok;
    QPushButton* reset;
public:
    CreazioneUtente(QWidget* parent =0);
    QLineEdit* getUser() const;
    QComboBox* getTipo() const;
    QLineEdit* getNome() const;
    QLineEdit* getCogn() const;
    QLineEdit* getEmail() const;
    QLineEdit* getConfEmail() const;
    QLineEdit* getPaswd() const;
    QLineEdit* getConfPaswd() const;
    QTextEdit* getContat() const;
    QPushButton* getOk() const;
    QPushButton* getReset() const;
public slots:
    void resetta();
};

#endif // CREAZIONEUTENTE

