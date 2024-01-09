#include "selectsum.h"
#include "restapidll.h"
#include "ui_selectsum.h"
#include <QDebug>
#include "ui_withdrawalfailed.h"
#include "ui_withdrawalsuccessful.h"
#include "withdrawalfailed.h"
#include "withdrawalsuccessful.h"

selectSum::selectSum(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectSum)
{
    ui->setupUi(this);

    RestApiDLL * RestApiDLLOlio3 = new RestApiDLL(this);
    connect(this, SIGNAL(sendAmountAndIdAccount(QString,float,QByteArray)), RestApiDLLOlio3, SLOT(receiveAmountAndIdAccount(QString,float,QByteArray)));

    connect(ui->nappi_sulje, SIGNAL(clicked(bool)), this, SLOT(on_nappi_muuta_summaa_clicked()));
    connect(ui->nappi_kirjaudu_ulos, SIGNAL(clicked(bool)), this, SLOT(on_nappi_kirjaudu_ulos_clicked()));

    // ajastin
    ajastinNosto = new QTimer(this);
    ajastinNosto->start(10*1000);
    qDebug()<<"Valise summa: ajastin 10 sek.";
    connect(ajastinNosto, &QTimer::timeout, this, &selectSum::timeOut);

    //olio kirjautumaan ulos:
    kirjauduUlosIkkuna = new logOut(this);

    connect(ui->nappi_kirjaudu_ulos, &QPushButton::clicked, this, &selectSum::on_nappi_kirjaudu_ulos_clicked);

    connect(kirjauduUlosIkkuna, &logOut::windowShown, [=]() { kirjauduUlosIkkuna->kaynnistaAjastinLogOut(); });
}

selectSum::~selectSum()
{
    delete ui;
}

void selectSum::timeOut()
{
    this->close();
    qDebug()<<"Valitse summa: timeOut, suljetaan ikkuna, paluu valikkoon.";
    delete ajastinNosto;
    selectActionMenu *valikkoNostosta = new selectActionMenu(this);
}

void selectSum::kaynnistaAjastinValitseSumma(){
    ajastinNosto->start();
    qDebug()<<"Valitse summa: käynnistetty ajastin 10 sek.";
}

void selectSum::on_nappi_muuta_summaa_clicked()
{
    ajastinNosto->stop();
    this->close();
    selectActionMenu *valikkoNostosta = new selectActionMenu(this);
}

void selectSum::on_nappi_kirjaudu_ulos_clicked()
{
    ajastinNosto->stop();
    kirjauduUlosIkkuna->show();
}

void selectSum::on_pushButton_20_clicked()
{
    ajastinNosto->stop();
    handlesum(20);
    qDebug()<<"valitse summa token: "+token;
}

void selectSum::on_pushButton_40_clicked()
{
    ajastinNosto->stop();
    handlesum(40);
}

void selectSum::on_pushButton_60_clicked()
{
    ajastinNosto->stop();
    handlesum(60);
}

void selectSum::on_pushButton_100_clicked()
{
    ajastinNosto->stop();
    handlesum(100);
}

void selectSum::on_pushButton_200_clicked()
{
    ajastinNosto->stop();
    handlesum(200);
}

void selectSum::on_pushButton_500_clicked()
{
    ajastinNosto->stop();
    handlesum(500);
}

void selectSum::handlesum(int sum)
{
    float saldo = AccountBalance.toFloat();
    saldo = saldo-sum;
    QString sumString;
    QString saldoString;
    if (sum > saldo)
    {
        qDebug()<<"Tilillä ei ole riittävästi saldoa";
        withdrawalFailed *withdrawalFailedOlio = new withdrawalFailed(this);
        withdrawalFailedOlio->ui->label_saldo->setText("Käytettävissä "+AccountBalance+" euroa.");
        withdrawalFailedOlio->open();

        //avataan nosto epäonnistunut ikkuna, josta palataan nappia painamalla takaisin selectsum -ikkunaan.
    }
    else
    {
        withdrawalSuccessful *withdrawalSuccessfulOlio = new withdrawalSuccessful(this);
        withdrawalSuccessfulOlio->ui->label_maara->setText(sumString.setNum(sum)+" euroa nostettu.");
        withdrawalSuccessfulOlio->ui->label_saldo->setText("Tilillä jäljellä " +saldoString.setNum(saldo)+" euroa.");
        withdrawalSuccessfulOlio->open();
        sum = -sum;
        emit sendAmountAndIdAccount(idTili, sum, token);
    }
}

void selectSum::setToken(const QByteArray &newToken)
{
    token = newToken;
}

void selectSum::setIdTili(const QString &newIdTili)
{
    idTili = newIdTili;
}

void selectSum::setAccountBalance(const QString &newAccountBalance)
{
    AccountBalance = newAccountBalance;
}

