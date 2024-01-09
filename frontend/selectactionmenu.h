#ifndef SELECTACTIONMENU_H
#define SELECTACTIONMENU_H

#include <QDialog>
#include "mainwindow.h"
#include "logout.h"

namespace Ui {
class selectActionMenu;
}

class selectActionMenu : public QDialog
{
    Q_OBJECT

public:
    explicit selectActionMenu(QWidget *parent = nullptr);
    ~selectActionMenu();
    void setKortti_nro(const QString &newKortti_nro);
    void setToken(const QByteArray &newToken);
    void setCustomerInfo(const QString &newCustomerInfo);

signals:
    void sendButtonAccountBalanceClicked(QByteArray, QString); // lähetetään signaalit napinpainamisesta RestApiDll:ään
    void sendButtonTransactionsClicked(QByteArray, QString);
    void sendButtonMakeAWithdrawalClicked(QByteArray, QString);

public slots:
    void kaynnistaAjastin();

private slots:
    void on_nappi_nayta_saldo_clicked(); // VALITSE TOIMINTO -ikkunan napit
    void on_nappi_nayta_tilitapahtumat_clicked();
    void on_nappi_kirjaudu_ulos_clicked();
    void on_nappi_nosta_rahaa_clicked();

    void receiveAccountBalanceInfo(QString, QString); // vastaanotetaan käsitelty http response stringinä.
    void receiveTransactionsInfo(QString);
    void receiveWithdrawalInfo(QString, QString);

    void ajastinTimeOut();

private:
    Ui::selectActionMenu *ui;
    QString kortti_nro;
    QByteArray token;
    QString customerInfo;
    QString idAccount;

    QString myBalanceData;
    QString myTransactionsData;
    QString myAccountTransactionsData;
    MainWindow *etusivu;

    QTimer *ajastin;
    logOut *kirjauduUlosIkkuna;
};

#endif // SELECTACTIONMENU_H
