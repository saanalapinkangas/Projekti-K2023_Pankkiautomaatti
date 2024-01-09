#include "showtransactions.h"
#include "ui_showtransactions.h"

showTransactions::showTransactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showTransactions)
{
    ui->setupUi(this);
    setWindowTitle("Tilitapahtumat");

    connect(ui->nappi_sulje, SIGNAL(clicked(bool)), this, SLOT(on_nappi_sulje_clicked()));
    connect(ui->nappi_kirjaudu_ulos, SIGNAL(clicked(bool)), this, SLOT(on_nappi_kirjaudu_ulos_clicked()));

    //ajastin:
    ajastinTilitapahtumat = new QTimer(this);
    ajastinTilitapahtumat->start(10 *1000);
    qDebug() << "tilitapahtumat: ajastin 10 sek";
    connect(ajastinTilitapahtumat, &QTimer::timeout, this, &showTransactions::timeOut);

    //mainwindow olio:
    etusivu = new MainWindow(this);

    //olio kirjautumaan ulos:
    kirjauduUlosIkkuna = new logOut(this);

    connect(ui->nappi_kirjaudu_ulos, &QPushButton::clicked, this, &showTransactions::on_nappi_kirjaudu_ulos_clicked);

    connect(kirjauduUlosIkkuna, &logOut::windowShown, [=]() { kirjauduUlosIkkuna->kaynnistaAjastinLogOut(); });


}

showTransactions::~showTransactions()
{
    delete ui;
}

void showTransactions::setShowMyTransactions(const QString &newShowMyTransactions)
{
    showMyTransactions = newShowMyTransactions;
    ui->TxtLabel_nayta_tilitapahtumat->setText(showMyTransactions);
}

void showTransactions::on_nappi_sulje_clicked()
{
    ajastinTilitapahtumat->stop();
    this->close();
    selectActionMenu *valikkoTilitapahtumista = new selectActionMenu(this);
    qDebug() << "tilitapahtumat: suljetaan tilitapahtumat, paluu valikkoon";
}


void showTransactions::on_nappi_kirjaudu_ulos_clicked()
{
    ajastinTilitapahtumat->stop();
    kirjauduUlosIkkuna->show();
    qDebug() << "tilitapahtumat: kirjauduttu ulos";
}

void showTransactions::timeOut()
{
    ajastinTilitapahtumat->stop();
    this->close();
    qDebug() << "tilitapahtumat: timeOut, suljetaan tilitapahtumat, paluu valikkoon";
    delete ajastinTilitapahtumat;
    selectActionMenu *valikkoTilitapahtumista = new selectActionMenu(this);
}
