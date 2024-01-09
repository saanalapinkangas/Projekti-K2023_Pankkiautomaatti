#include "login.h"
#include "restapidll.h"
#include "selectactionmenu.h"
#include "ui_login.h"
#include <QDebug>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("Login");

    //avataan pin-ikkuna klikatessa:
    connect(ui->addPin, SIGNAL(clicked(bool)), this, SLOT(openPinWindow()));

    //ajastin kortin lukitsemiselle:
    kortinLukitus = new QTimer(this);
    connect(kortinLukitus, &QTimer::timeout, this, &login::ajastinKortinLukitus);

    //poistu-nappi:
    connect(ui->pushButton_poistu,SIGNAL(clicked(bool)),this,SLOT(poistu_nappi()));

    //tähän connect restapiin.
    RestApiDLL *RestApiDLLOlio = new RestApiDLL(this);
    connect(this, SIGNAL(sendCardNumber(QString)), RestApiDLLOlio, SLOT(receiveCardNumber(QString)));
    connect(this, SIGNAL(sendPinNumber(QString)), RestApiDLLOlio, SLOT(receivePinNumber(QString)));
    connect(this, SIGNAL(ButtonLoginClicked()), RestApiDLLOlio, SLOT(receiveButtonLoginClicked()));
    connect(this, SIGNAL(findCustomerInfo(QByteArray,QString)), RestApiDLLOlio, SLOT(receiveFindCustomerInfo(QByteArray,QString)));

    connect(RestApiDLLOlio, SIGNAL(sendLoginInfo(QByteArray,QString)), this, SLOT(receiveLoginInfo(QByteArray,QString)));
    connect(RestApiDLLOlio, SIGNAL(sendCustomerInfo(QString)), SLOT(receiveCustomerInfo(QString)));
}

login::~login()
{
    delete ui;
}

void login::receiveCardNumber(const QString cardNumber)
{
    this->cardNumber = cardNumber;
    qDebug() << "korttinumero: " << cardNumber;
    ui->lineEdit_kortti_nro->setText(cardNumber);
}

void login::openPinWindow()
{
    ppinUI = new pinUI(this);
    connect(ppinUI, SIGNAL(sendPin(QByteArray)), this,SLOT(receivePinNumber(QByteArray)));

    ppinUI->open();
}

void login::receivePinNumber(QByteArray num)
{
    pinNumber = num;

    pinString = QString::fromUtf8(pinNumber); // muunnetaan bytet stringiksi
    QString maskedPin = QString(pinString.size(), '*'); // muunnettaan teksti tähdiksi
    ui->addPin->setText(maskedPin);

    delete ppinUI;
    ppinUI = nullptr;
}

void login::on_nappi_kirjaudu_clicked()
{
    emit sendCardNumber(cardNumber);
    emit sendPinNumber(pinString);
    emit ButtonLoginClicked();
    qDebug()<<"Painettu kirjaudu-nappia login.cpp";
    qDebug()<<"Korttinumero: "+cardNumber;
    qDebug()<<"Pin-koodi: "+pinString;
}

void login::receiveLoginInfo(QByteArray responseData, QString cardNum)
{
    kierrosPin--;
    qDebug()<<"Kierrokset: "<<kierrosPin;
    response_data = responseData;
    kortti_nro = cardNum;
    qDebug()<<"receiveLoginInfoSlot.";
    token = "Bearer "+responseData;
    qDebug()<<token;
    qDebug()<<"Korttinumero: "+cardNum;
    emit findCustomerInfo(token, cardNum);

    if (responseData.length() == 0 || QString::compare(responseData, "-4078") == 0 || QString::compare(responseData, "1045") == 0) {
        ui->label_kirjautumisinfo->setText("Virhe tietokantayhteydessä.");
        ui->lineEdit_kortti_nro->setText(cardNumber);
        ui->addPin->setText("Anna PIN-koodi");
        kierrosPin=3;
    }

    else {
        if (QString::compare(responseData, "false") != 0) {
        ui->label_kirjautumisinfo->setText("Login OK.");
        ui->lineEdit_kortti_nro->setText(cardNumber);
        ui->addPin->setText("Anna PIN-koodi");
        qDebug()<<"login.cpp: Login OK, avaattiin Valitse toiminto-menu";
        }

        if (kierrosPin==0) {
        kortinLukitus->start(10 * 60 *1000); // ajastin 10 min, "kortin lukitus"
        ui->label_kirjautumisinfo->setText("Annoit väärän PIN-koodin 3 kertaa.");
        ui->label_kirjautumisinfo_2->setText("Korttisi on lukittu 10 minuutiksi.");
        ui->addPin->setText("Anna PIN-koodi");
        ui->nappi_kirjaudu->setEnabled(false);  // lukitse kirjaudu-nappi
        ui->addPin->setEnabled(false);  //lukitse pinkoodin syöttö
        }

            else {
            ui->label_kirjautumisinfo->setText("Virheellinen PIN-koodi.");
            ui->label_kirjautumisinfo_2->setText("Yrityksiä jäljellä: " + QString::number(kierrosPin));
            ui->addPin->setText("Anna PIN-koodi");
        }
    }
}

void login::receiveCustomerInfo(QString customerData)
{
    customerInfo = customerData;
    qDebug()<<"customerdata, :"+customerInfo;
    if(customerData.length() != 0) {
        selectActionMenu * selectActionMenuOlio = new selectActionMenu(this);
        selectActionMenuOlio->setCustomerInfo(customerData);
        selectActionMenuOlio->setKortti_nro(kortti_nro);
        selectActionMenuOlio->setToken(token);
        selectActionMenuOlio->open();
        }
    else {qDebug()<<"Login epäonnistui.";}
    }

void login::setCustomerInfo(const QString &newCustomerInfo)
{
    customerInfo = newCustomerInfo;
}

void login::ajastinKortinLukitus()
{
    ui->nappi_kirjaudu->setEnabled(true);   // vapauta kirjautumisnappi käyttöön
    ui->addPin->setEnabled(true);   // vapauta pin-koodin syöttö
    ui->label_kirjautumisinfo->clear();
    ui->label_kirjautumisinfo_2->clear();
    kierrosPin=3;
}

void login::ajastinTimeout()
{
    this->close(); //yleinen ajastimen loppuminen eli ikkunoiden sulkeminen,
}

void login::poistu_nappi() // jos tästä painaa, niin minä en ainakaan saanut kortinlukijaa lukemaan korttia uudestaan.
{
    this->close();
}

void login::kirjaudu_ulos_nappi() // Onko tälläistä nappia olemassa? Ei ainakaan tee mitään?
{
    //QApplication::closeAllWindows();

}
