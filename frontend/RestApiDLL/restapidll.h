#ifndef RESTAPIDLL_H
#define RESTAPIDLL_H

#include "RestApiDLL_global.h"
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class RESTAPIDLL_EXPORT RestApiDLL : public QObject
{
    Q_OBJECT
public:
    RestApiDLL(QObject *parent);
    ~RestApiDLL();

private:
    QString baseURL = "http://localhost:3000";
    QString  kortti_nro;
    QByteArray token;
    QString pin;

    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;

    QNetworkReply *reply;
    QByteArray response_data;

signals:
    void sendLoginInfo(QByteArray response_data, QString token); // lähetetään exeen käsitelty http-response.
    void sendCustomerInfo(QString customerInfo);
    void sendAccountBalanceInfoToSelectActionMenu(QString myAccountBalanceData, QString myTransactionsData);
    void sendTransactionsInfoToSelectActionMenu(QString myAccountTransactionsData);
    void sendWithdrawalInfoToSelectActionMenu(QString myAccountBalanceData, QString idAccount);

private slots:
    void receiveCardNumber(QString cnum); // täällä vastaanotetaan tieto rfid ja pin dll:stä ja tallennetaan muuttujaan.
    void receivePinNumber(QString pnum);

    void receiveButtonLoginClicked(); // täällä vastaanotetaan signaali exestä ja tehdään http request
    void receiveFindCustomerInfo(QByteArray, QString);
    void receiveButtonAccountBalanceClicked(QByteArray myToken, QString cardNum);
    void receiveButtonTransactionsClicked(QByteArray myToken, QString cardNum);
    void receiveButtonMakeAWithdrawalClicked(QByteArray myToken, QString cardNum);
    void receiveAmountAndIdAccount(QString, float, QByteArray); // Vastaanotetaan uusi saldo selectsum-ikkunasta.

    void addLoginSlot (QNetworkReply *reply); // täällä käsitellään http request ja lähtetään signaali exeen.
    void getMyCustomerInfoSlot(QNetworkReply *reply);
    void getMyAccountBalanceSlot (QNetworkReply *reply);
    void getMyTransactionsSlot (QNetworkReply *reply);
    void getMyWithdrawalInfoSlot (QNetworkReply *reply);
    void addMyAccountTransactionSlot(QNetworkReply *reply);
};


#endif // RESTAPIDLL_H
