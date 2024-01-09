#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    pDll = new DLL_rfid(this);
    connect (pDll, SIGNAL(cardRead(QByteArray)), this, SLOT(receiveData(QByteArray)));
    pDll->openSerialPort();

    pLoginWindow = new login(this);

    //ajastin = new QTimer(this);
    //connect(ajastin, &QTimer::timeout, this, &MainWindow::ajastinTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::receiveData(QByteArray c)
{
    QString DataAsString = QString(c);
    cardNumber = DataAsString;  // tallennetaan kortin numero
    qDebug() << "kortin id saatu, cardNumber" << cardNumber;

    connect(this, &MainWindow::sendCardNumber, pLoginWindow, &login::receiveCardNumber);
    emit sendCardNumber(cardNumber);

    pLoginWindow->open();
    qDebug() << "avataan kirjautumisikkuna";

    delete pDll;
}

void MainWindow::ajastinTimeout()
{
    //ui->nappi_kirjaudu->setEnabled(true);   // vapauta kirjautumisnappi käyttöön
    qDebug() << "kirjatumisnappi käytössä";
}

