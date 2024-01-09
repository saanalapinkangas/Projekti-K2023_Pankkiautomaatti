#include "restapidll.h"

RestApiDLL::RestApiDLL(QObject *parent)
{
    //qDebug() << "RestApiDLL konstruktori";
}

RestApiDLL::~RestApiDLL()
{
    //qDebug()<<"RestApiDLL destruktori.";
}

void RestApiDLL::receiveCardNumber(QString cnum)
{
    kortti_nro = cnum; // täällä pitäis vastaanottaa RFID-dll:ltä korttinumero ja asettaa se muuttujaan korttinro.
    qDebug()<<"RestApiDLL, vastaanotetaan korttinumero: "+kortti_nro;
}

void RestApiDLL::receivePinNumber(QString pnum)
{
    pin = pnum; // täällä pitäis vastaanottaa pinUI-dll:ltä se pin-koodi ja asettaa se muuttujaan pin.
    qDebug()<<"RestApiDLL, vastaanotetaan pin-koodi: "+pin;
}

void RestApiDLL::receiveButtonLoginClicked()
{
    qDebug()<<"KORTTINRO: "+kortti_nro;
    qDebug()<<"PIN: "+pin;

    QJsonObject jsonObj;
    jsonObj.insert("kortti_nro", kortti_nro);
    jsonObj.insert("pin", pin);
    QString site_url = baseURL+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addLoginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiDLL::addLoginSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    token = "Bearer "+response_data;
    qDebug()<<"responsedata: "+response_data;
    emit sendLoginInfo(response_data, kortti_nro);
    reply->deleteLater();
    loginManager->deleteLater();
}


void RestApiDLL::receiveFindCustomerInfo(QByteArray myToken, QString cardNum)
{
    kortti_nro = cardNum;
    token = myToken;
    qDebug()<<"FIND CUSTOMERINFO, korttinumero: "+kortti_nro;
    qDebug()<<"FIND CUSTOMERINFO, token: "+token;
    QString site_url = baseURL+"/asiakas/"+kortti_nro;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));
    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyCustomerInfoSlot(QNetworkReply*)));
    reply = getManager->get(request);
}


void RestApiDLL::getMyCustomerInfoSlot(QNetworkReply *reply)
{
    QString customerInfo;
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        customerInfo = json_obj["Etunimi"].toString()+" "+json_obj["Sukunimi"].toString()+"! || "+json_obj["DebitTilinro"].toString()+" "
                       +json_obj["CreditTilinro"].toString();
    }

    qDebug()<<"GET CUSTOMERINFO: "+customerInfo; // täällä info OK.
    emit sendCustomerInfo(customerInfo);
    reply->deleteLater();
    getManager->deleteLater();
}

void RestApiDLL::receiveButtonAccountBalanceClicked(QByteArray myToken, QString cardNum)
{
    token = myToken;
    kortti_nro = cardNum;
    QString site_url = baseURL+"/tili/"+kortti_nro;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));
    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyAccountBalanceSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

void RestApiDLL::getMyAccountBalanceSlot(QNetworkReply *reply)
{
    QString myAccountBalanceData;
    QString myTransactionsData;
    response_data = reply->readAll();
    qDebug()<<"restapidll.cpp: getMyAccountBalanceSlot.";
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QJsonArray json_array = json_doc.array();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        myAccountBalanceData = "Tilin omistaja: "+json_obj["Etunimi"].toString()+" "+json_obj["Sukunimi"].toString()+"\n\n"+
                               "Tilinumero: "+json_obj["DebitTilinro"].toString()+json_obj["CreditTilinro"].toString()+"\n\n"+
                               "Tilillä on käytettävissä: "+json_obj["DebitSaldo"].toString()+json_obj["CreditSaldo"].toString()+" euroa.";
        myTransactionsData += "\n"+json_obj["Maara"].toString()+" || "+json_obj["Tapahtuma"].toString()+" || "+json_obj["PVM"].toString()+"\n";
    }
    emit sendAccountBalanceInfoToSelectActionMenu(myAccountBalanceData, myTransactionsData);
    qDebug()<<"restapidll.cpp: signaali sendAccountBalanceInfoToSelectActionMenu lähetetty.";
                reply->deleteLater();
    getManager->deleteLater();
}

void RestApiDLL::receiveButtonTransactionsClicked(QByteArray myToken, QString cardNum)
{
    token = myToken;
    kortti_nro = cardNum;
    QString site_url = baseURL+"/tilitapahtumat/"+kortti_nro;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));
    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyTransactionsSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

void RestApiDLL::getMyTransactionsSlot(QNetworkReply *reply)
{
    QString myAccountTransactionsData;
    response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        myAccountTransactionsData += json_obj["Maara"].toString()+" €"+" || "+json_obj["Tapahtuma"].toString()+" || "+(json_obj["PVM"].toString())+"\n\n";
    }

    emit sendTransactionsInfoToSelectActionMenu(myAccountTransactionsData);
    reply->deleteLater();
    getManager->deleteLater();
}

void RestApiDLL::receiveButtonMakeAWithdrawalClicked(QByteArray myToken, QString cardNum)
{
    token = myToken;
    kortti_nro = cardNum;
    qDebug()<<"restapidll.cpp: receiveButtonAccountBalanceClicked";
    QString site_url = baseURL+"/tili/"+kortti_nro;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(token));
    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyWithdrawalInfoSlot(QNetworkReply*)));
    reply = getManager->get(request);
}


void RestApiDLL::getMyWithdrawalInfoSlot(QNetworkReply *reply) // täällä lähetetään tilin saldo (myAccountBalanceData) ja idTili (idAccount)
{
    response_data = reply->readAll();
    qDebug()<<"restapidll.cpp: getMyWithdrawalSlot.";

    QString idAccount;
    QString myAccountBalanceData;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QJsonArray json_array = json_doc.array();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        myAccountBalanceData = json_obj["DebitSaldo"].toString()+json_obj["CreditSaldo"].toString();
        idAccount = QString::number(json_obj["idTili"].toInt());
    }
    qDebug()<<"ID-tili: "+idAccount;
    qDebug()<<"Saldo: "+myAccountBalanceData;
    emit sendWithdrawalInfoToSelectActionMenu(myAccountBalanceData, idAccount);
    qDebug()<<"restapidll.cpp: signaali sendWithdrawalInfo lähetetty.";
                reply->deleteLater();
    getManager->deleteLater();
}

void RestApiDLL::receiveAmountAndIdAccount(QString idTili, float amount, QByteArray myToken) // Tähän pitäis tulla selectSum-ikkunasta idTili, noston suuruus ja token.
{
    QString idAccount = idTili;
    float maara = amount;
    token = myToken;
    QJsonObject jsonObj;
    jsonObj.insert("idTili", idAccount);
    jsonObj.insert("tapahtuma","Nosto");
    jsonObj.insert("maara", maara);

    qDebug()<<"RestApiDLL.cpp, receiveAmountAndIdAccount";

    QString site_url="http://localhost:3000/tili/";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"),(token));
    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(addMyAccountTransactionSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void RestApiDLL::addMyAccountTransactionSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"responseData: "+response_data;
    reply->deleteLater();
    postManager->deleteLater();
}
