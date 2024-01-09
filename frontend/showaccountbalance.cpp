#include "showaccountbalance.h"
#include "ui_showaccountbalance.h"

showAccountBalance::showAccountBalance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showAccountBalance)
{
    ui->setupUi(this);
    setWindowTitle("Tilin saldo");

    connect(ui->nappi_sulje_ikkuna, SIGNAL(clicked(bool)), this, SLOT(on_nappi_sulje_ikkuna_clicked()));
    connect(ui->nappi_kirjaudu_ulos, SIGNAL(clicked(bool)), this, SLOT(on_nappi_kirjaudu_ulos_clicked()));

    //ajastin:
    ajastinSaldo = new QTimer(this);
    ajastinSaldo->start(10 *1000);
    qDebug() << "Saldo: ajastin 10 sek";
    connect(ajastinSaldo, &QTimer::timeout, this, &showAccountBalance::timeOut);

    //olio kirjautumaan ulos:
    kirjauduUlosIkkuna = new logOut(this);

    connect(ui->nappi_kirjaudu_ulos, &QPushButton::clicked, this, &showAccountBalance::on_nappi_kirjaudu_ulos_clicked);

    connect(kirjauduUlosIkkuna, &logOut::windowShown, [=]() { kirjauduUlosIkkuna->kaynnistaAjastinLogOut(); });


}

showAccountBalance::~showAccountBalance()
{
    delete ui;
}

void showAccountBalance::setShowMyAccountBalance(const QString &newShowMyAccountBalance)
{
    showMyAccountBalance = newShowMyAccountBalance;
    ui->TxtLabel_omistajan_tiedot->setText(showMyAccountBalance);
}
void showAccountBalance::setShowMyAccountTransactions(const QString &newShowMyAccountTransactions)
{
    showMyAccountTransactions = newShowMyAccountTransactions;
    ui->TxtLabel_tilitapahtumat->setText(newShowMyAccountTransactions);
}

// sulje-nappi NÄYTÄ SALDO-ikkunassa.
void showAccountBalance::on_nappi_sulje_ikkuna_clicked()
{
    ajastinSaldo->stop();
    this->close();
    selectActionMenu *valikkoSaldosta = new selectActionMenu(this);
    qDebug() << "Saldo: suljetaan saldo, paluu valikkoon";
}

// kirjaudu ulos:
void showAccountBalance::on_nappi_kirjaudu_ulos_clicked()
{
    ajastinSaldo->stop();
    kirjauduUlosIkkuna->show();
    qDebug() << "Saldo: kirjauduttu ulos";
}

// aika loppuu:
void showAccountBalance::timeOut()
{
    ajastinSaldo->stop();
    this->close();
    qDebug() << "Saldo: timeOut, suljetaan saldo, paluu valikkoon";
    delete ajastinSaldo;
    selectActionMenu *valikkoSaldosta = new selectActionMenu(this);
    qDebug() << "kaynnistetään valikon ajastin";
}



