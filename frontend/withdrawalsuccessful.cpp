#include "withdrawalsuccessful.h"
#include "ui_withdrawalsuccessful.h"

withdrawalSuccessful::withdrawalSuccessful(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::withdrawalSuccessful)
{
    ui->setupUi(this);

    connect(ui->nappi_sulje, SIGNAL(clicked(bool)), this,
    SLOT(on_nappi_sulje_clicked()));

    //ajastin:
    ajastinNostoOK = new QTimer(this);
    ajastinNostoOK->start(10 *1000);
    qDebug() << "Nosto ok: ajastin 10 sek";
    connect(ajastinNostoOK, &QTimer::timeout, this, &withdrawalSuccessful::timeOut);

}

withdrawalSuccessful::~withdrawalSuccessful()
{
    delete ui;
}

void withdrawalSuccessful::on_nappi_sulje_clicked()
{
    this->close(); //tästä pitäisi mennä selectactionmenu-ikkunaan
    valikkoNostoOK = new selectActionMenu(this);
}

void withdrawalSuccessful::timeOut()
{
    this->close();
    qDebug() << "Nosto hylätty: timeOut, suljetaan, paluu valikkoon";
    delete ajastinNostoOK;
    valikkoNostoOK = new selectActionMenu(this);

}
