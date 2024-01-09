#include "withdrawalfailed.h"
#include "ui_withdrawalfailed.h"

withdrawalFailed::withdrawalFailed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdrawalFailed)
{
    ui->setupUi(this);

    connect(ui->nappi_kirjaudu_ulos, SIGNAL(clicked(bool)), this, SLOT(on_nappi_kirjaudu_ulos_clicked()));

    kirjauduUlosIkkuna = new logOut(this);
    connect(ui->nappi_kirjaudu_ulos, &QPushButton::clicked, this,
            &withdrawalFailed::on_nappi_kirjaudu_ulos_clicked);
    connect(kirjauduUlosIkkuna, &logOut::windowShown, [=]()
    {kirjauduUlosIkkuna->kaynnistaAjastinLogOut();});

    // ajastin
    ajastinNostoFail = new QTimer(this);
    ajastinNostoFail->start(10 *1000);
    qDebug()<<"Nosto hylätty: ajastin 10 sek";

    connect(ajastinNostoFail, &QTimer::timeout, this, &withdrawalFailed::timeOut);
}

withdrawalFailed::~withdrawalFailed()
{
    delete ui;
}

void withdrawalFailed::on_nappi_muuta_summaa_clicked()
{
    this->close(); //tästä pitäisi mennä selectsum-ikkunaan
    valitseSumma = new selectSum(this);
    valitseSumma->kaynnistaAjastinValitseSumma();
}

void withdrawalFailed::on_nappi_kirjaudu_ulos_clicked()
{
   // this->close(); //tästä pitäisi mennä selectactionmenu -ikkunaan
   // valikkoNostoFail = new selectActionMenu(this);
    ajastinNostoFail->stop();
    kirjauduUlosIkkuna->show();
}

void withdrawalFailed::timeOut()
{
    this->close();
    qDebug() << "Nosto hylätty: timeOut, suljetaan, paluu valikkoon";
    delete ajastinNostoFail;
    valikkoNostoFail = new selectActionMenu(this);
}
