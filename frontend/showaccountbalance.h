#ifndef SHOWACCOUNTBALANCE_H
#define SHOWACCOUNTBALANCE_H

#include <QDialog>
#include "selectactionmenu.h"

namespace Ui {
class showAccountBalance;
}

class showAccountBalance : public QDialog
{
    Q_OBJECT

public:
    explicit showAccountBalance(QWidget *parent = nullptr);
    ~showAccountBalance();
    void setShowMyAccountBalance(const QString &newShowMyAccountBalance);
    void setShowMyAccountTransactions(const QString &newShowMyAccountTransactions);

signals:
    void kirjauduUlosSignaali();

private slots:
    void on_nappi_sulje_ikkuna_clicked();
    void on_nappi_kirjaudu_ulos_clicked();
    void timeOut();

private:
    Ui::showAccountBalance *ui;
    QString showMyAccountBalance;
    QString showMyAccountTransactions;

    QTimer *ajastinSaldo;
    logOut *kirjauduUlosIkkuna;
};

#endif // SHOWACCOUNTBALANCE_H
