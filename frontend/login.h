#ifndef LOGIN_COPY_H
#define LOGIN_COPY_H

#include <QMainWindow>
#include <QDialog>
#include <QApplication>
#include <QCoreApplication>
#include "pinui.h"
#include "restapidll.h" // tätä ei kestä poistaa vaikka se herjaa.

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QTimer *ajastin;


    void setCustomerInfo(const QString &newCustomerInfo);

signals:
    void sendCardNumber(QString);
    void sendPinNumber(QString);

    void ButtonLoginClicked();
    void findCustomerInfo(QByteArray, QString);

public slots:
    void receiveCardNumber(const QString cardNumber);
    void poistu_nappi();
    void kirjaudu_ulos_nappi();

private slots:
    void openPinWindow();
    void receivePinNumber (QByteArray);
    void ajastinKortinLukitus();
    void ajastinTimeout();

    void on_nappi_kirjaudu_clicked();
    void receiveLoginInfo(QByteArray, QString);
    void receiveCustomerInfo(QString);

private:
    Ui::login *ui;
    QString cardNumber;
    pinUI * ppinUI;
    QByteArray pinNumber;

    QString kortti_nro;
    QByteArray token;
    QString customerInfo;
    QString customerData; // onko tarpeen?
    QByteArray response_data; // onko tarpeen?

    QTimer *kortinLukitus;
    int kierrosPin=3;
    QString pinString;
};

#endif // LOGIN_COPY_H





// TÄSSÄ ALLA ON MUOKKAAMATON MIKÄ TOIMII!!
/*#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QDialog>
#include <QApplication>
#include <QCoreApplication>
#include "pinui.h"

//Nämä http:tä varten
#include <QtNetwork>                // Mahdollistaa TCT/IP-protokollan käytön.
#include <QNetworkAccessManager>    // Mahdollistaa http-requestien ja -responsien lähettämisen/vastaanottamisen.
#include <QJsonDocument>            // Mahdollistaa json-dokumenttien lukemisen ja kirjoittamisen.


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QTimer *ajastin;

public slots:
    void receiveCardNumber(const QString cardNumber);
    void poistu_nappi();
    void kirjaudu_ulos_nappi();

private slots:
    void openPinWindow();
    void receivePinNumber (QByteArray); //-------
    void on_nappi_kirjaudu_clicked();
    void addLoginSlot (QNetworkReply *reply);
    void ajastinKortinLukitus();
    void ajastinTimeout();

private:
    Ui::login *ui;
    QString cardNumber;
    pinUI * ppinUI;
    QByteArray pinNumber; //--------

    QString kortti_nro; // Käytetään käyttäjätunnuksena.

    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray token;

    QTimer *kortinLukitus;
    int kierrosPin=3;
    QString pinString;
};

#endif // LOGIN_H*/
