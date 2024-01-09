#include "logout.h"
#include "ui_logout.h"

logOut::logOut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logOut)
{
    ui->setupUi(this);
    setWindowTitle("Kirjaudu ulos");

    //mainwindow olio:
    etusivuLogOut = new MainWindow(this);

    ajastinLogOut = new QTimer(this);
    connect(ajastinLogOut, &QTimer::timeout, [=]() {
        this->close();
    });
}

logOut::~logOut()
{
    delete ui;
}

void logOut::setLogMeOut(const QString &newLogMeOut)
{
    logMeOut = newLogMeOut;
}

void logOut::kaynnistaAjastinLogOut()
{
    ajastinLogOut->start(10 *1000);
    qDebug() << "Kirjauduttu ulos: ajastin 10 sek";
    connect(ajastinLogOut, &QTimer::timeout, this, &logOut::timeOut);
}

void logOut::timeOut()
{
    QApplication::closeAllWindows();
    qDebug() << "Kirjaudu ulos: timeOut, suljetaan ikkuna, paluu valikkoon";
    delete ajastinLogOut;
    etusivuLogOut->show();
}

void logOut::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    // Emitoidaan signaali kun Logout-ikkuna on näytetty
    emit windowShown();
}

