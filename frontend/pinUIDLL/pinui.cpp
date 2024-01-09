#include "pinui.h"
#include "ui_pinui.h"

pinUI::pinUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pinUI)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),
            this,SLOT(clickHandler()));

    connect(ui->pushButton_2,SIGNAL(clicked(bool)),
            this,SLOT(clickHandler2()));
}

pinUI::~pinUI()
{
    delete ui;
}

void pinUI::clickHandler()
{
    //QString luku = ui->lineEdit->text();
    //emit sendPin(luku.toShort());

    QString luku = ui->lineEdit->text();
    QByteArray koodi = luku.toUtf8();
    emit sendPin(koodi);
}

void pinUI::clickHandler2() //peruuta-ikkuna
{
    this->close();
}
