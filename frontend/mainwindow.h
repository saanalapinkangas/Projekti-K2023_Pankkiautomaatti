#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dll_rfid.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow  : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendCardNumber(const QString cardNumber);


private slots:
    void receiveData(QByteArray c); // haetaan kortin tunnus
    void ajastinTimeout();  // AJASTIN EI TOIMI VIELÄ


private:
    Ui::MainWindow *ui;

    DLL_rfid * pDll;    // haetaan rfid-lukijan tiedot
    login * pLoginWindow;   // olio login-ikkunalle
    QString cardNumber;
    QTimer *ajastin;
    int ajastin10min=10;
};
#endif // MAINWINDOW_H
