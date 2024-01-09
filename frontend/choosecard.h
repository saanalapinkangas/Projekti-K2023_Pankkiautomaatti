/*#ifndef CHOOSECARD_H
#define CHOOSECARD_H

#include <QDialog>
#include <QMainWindow>
#include "login.h"

namespace Ui {
class chooseCard;
}

class chooseCard : public QDialog
{
    Q_OBJECT

public:
    explicit chooseCard(QWidget *parent = nullptr);
    ~chooseCard();
    QString cardNumber;

public slots:
    void addLoginSlot (QNetworkReply *reply);
    void avaaTili();

private:
    Ui::chooseCard *ui;
    QString kortti_nro; // Käytetään käyttäjätunnuksena.

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;
};

#endif // CHOOSECARD_H*/
