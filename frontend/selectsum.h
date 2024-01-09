#ifndef SELECTSUM_H
#define SELECTSUM_H

#include <QDialog>
#include "selectactionmenu.h"

namespace Ui {
class selectSum;
}

class selectSum : public QDialog
{
    Q_OBJECT

public:
    explicit selectSum(QWidget *parent = nullptr);
    ~selectSum();

    void setAccountBalance(const QString &newAccountBalance);
    void setIdTili(const QString &newIdTili);
    void setToken(const QByteArray &newToken);

signals:
    void sendAmountAndIdAccount(QString, float, QByteArray);

public slots:
    void kaynnistaAjastinValitseSumma();

private slots:
    void on_pushButton_20_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_60_clicked();
    void on_pushButton_100_clicked();
    void on_pushButton_200_clicked();
    void on_pushButton_500_clicked();

    void on_nappi_muuta_summaa_clicked();
    void on_nappi_kirjaudu_ulos_clicked();

    void timeOut();

private:
    Ui::selectSum *ui;
    QByteArray token;
    QString kortti_nro;
    QString idTili;
    QString AccountBalance;

    void handlesum(int sum);

    QTimer *ajastinNosto;
    logOut *kirjauduUlosIkkuna;
};

#endif // SELECTSUM_H
