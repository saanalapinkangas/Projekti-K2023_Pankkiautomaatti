#include "selectactionmenu.h"
#include "qobjectdefs.h"
#include "selectsum.h"
#include "showaccountbalance.h"
#include "showtransactions.h"
#include "ui_selectactionmenu.h"
#include "restapidll.h"
#include "mainwindow.h"


selectActionMenu::selectActionMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectActionMenu)
{
    ui->setupUi(this);
    setWindowTitle("Valitse toiminto");

    RestApiDLL *RestApiDLLOlio2 = new RestApiDLL(this);
    connect(this, SIGNAL(sendButtonAccountBalanceClicked(QByteArray,QString)), RestApiDLLOlio2, SLOT(receiveButtonAccountBalanceClicked(QByteArray,QString)));
    connect(this, SIGNAL(sendButtonTransactionsClicked(QByteArray,QString)), RestApiDLLOlio2, SLOT(receiveButtonTransactionsClicked(QByteArray,QString)));
    connect(this, SIGNAL(sendButtonMakeAWithdrawalClicked(QByteArray,QString)), RestApiDLLOlio2, SLOT(receiveButtonMakeAWithdrawalClicked(QByteArray,QString)));

    connect(RestApiDLLOlio2, SIGNAL(sendAccountBalanceInfoToSelectActionMenu(QString,QString)), this, SLOT(receiveAccountBalanceInfo(QString,QString)));
    connect(RestApiDLLOlio2, SIGNAL(sendTransactionsInfoToSelectActionMenu(QString)), this, SLOT(receiveTransactionsInfo(QString)));
    connect(RestApiDLLOlio2, SIGNAL(sendWithdrawalInfoToSelectActionMenu(QString,QString)), this, SLOT(receiveWithdrawalInfo(QString,QString)));

    //ajastin 30 sekuntia, palataan alkunäyttöön:
    ajastin = new QTimer(this);
    selectActionMenu::kaynnistaAjastin();
    connect(ajastin, &QTimer::timeout, this, &selectActionMenu::ajastinTimeOut);

    //olio mainwindowin esiin nostamiseen:
    etusivu = new MainWindow(this);

    //olio kirjautumaan ulos:
    kirjauduUlosIkkuna = new logOut(this);

    connect(ui->nappi_kirjaudu_ulos, &QPushButton::clicked, this, &selectActionMenu::on_nappi_kirjaudu_ulos_clicked);

    connect(kirjauduUlosIkkuna, &logOut::windowShown, [=]() { kirjauduUlosIkkuna->kaynnistaAjastinLogOut(); });
}

selectActionMenu::~selectActionMenu()
{
    delete ui;
}
/*
const QString &selectActionMenu::getKortti_nro() const
{
    return kortti_nro;
}*/

void selectActionMenu::setKortti_nro(const QString &newKortti_nro)
{
    kortti_nro = newKortti_nro;
}

void selectActionMenu::setToken(const QByteArray &newToken)
{
    token = newToken;
}

void selectActionMenu::setCustomerInfo(const QString &newCustomerInfo)
{
    customerInfo = newCustomerInfo;
    ui->label_asiakkaan_tiedot->setText("Tervetuloa "+customerInfo);
}

//Näytä saldo -nappi
void selectActionMenu::on_nappi_nayta_saldo_clicked()
{
    ajastin->stop();
    qDebug() << "Valikko: ajastin keskeytetty, saldo-nappi";
    QString cardNum = kortti_nro;
    QByteArray myToken = token;
    emit sendButtonAccountBalanceClicked(myToken, cardNum);
}

//Näytä tilitapahtumat -nappi
void selectActionMenu::on_nappi_nayta_tilitapahtumat_clicked()
{
    ajastin->stop();
    qDebug() << "Valikko: ajastin keskeytetty, tilitapahtumat-nappi";
    QString cardNum = kortti_nro;
    QByteArray myToken = token;
    emit sendButtonTransactionsClicked(myToken, cardNum);
}

//Nosta rahaa -nappi
void selectActionMenu::on_nappi_nosta_rahaa_clicked()
{
    ajastin->stop();
    qDebug() << "Valikko: ajastin keskeytetty, nosto-nappi";
    QString cardNum = kortti_nro;
    QByteArray myToken = token;
    emit sendButtonMakeAWithdrawalClicked(myToken, cardNum);
}

void selectActionMenu::receiveAccountBalanceInfo(QString myBalance, QString myTransactions)
{
    myBalanceData = myBalance;
    myTransactionsData = myTransactions;
    showAccountBalance *showMyAccountBalanceOlio = new showAccountBalance(this);
    showMyAccountBalanceOlio->setShowMyAccountBalance(myBalance);
    showMyAccountBalanceOlio->setShowMyAccountTransactions(myTransactions);
    showMyAccountBalanceOlio->open();
}

void selectActionMenu::receiveTransactionsInfo(QString myTransactions)
{
    myAccountTransactionsData = myTransactions;
    showTransactions *showMyTransactionsOlio = new showTransactions(this);
    showMyTransactionsOlio->setShowMyTransactions(myTransactions);
    showMyTransactionsOlio->open();
}

void selectActionMenu::receiveWithdrawalInfo(QString BalanceData, QString MyAccountID)
{
    myBalanceData = BalanceData;
    idAccount = MyAccountID;
    qDebug()<<"idTili: "+MyAccountID;
    selectSum *selectSumOlio = new selectSum(this);
    selectSumOlio->setAccountBalance(BalanceData);
    selectSumOlio->setToken(token);
    selectSumOlio->setIdTili(MyAccountID);
    selectSumOlio->open();
}

void selectActionMenu::ajastinTimeOut()
{
    delete ajastin;
    QApplication::closeAllWindows();
    etusivu->show();
    qDebug() << "Valikko: 30 sekuntia kulunut, palataan mainwindowiin";
}

void selectActionMenu::kaynnistaAjastin()
{
    ajastin->start(30 *1000);
    qDebug() << "Valikko: käynnistetty ajastin 30 sek";
}

// KIRJAUDU ULOS -nappi
void selectActionMenu::on_nappi_kirjaudu_ulos_clicked()
{
    ajastin->stop();
    kirjauduUlosIkkuna->show();
    qDebug() << "Valikko: kirjauduttu ulos, palataan mainwindowiin";
}


