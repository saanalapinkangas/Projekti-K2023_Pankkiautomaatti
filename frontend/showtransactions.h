#ifndef SHOWTRANSACTIONS_H
#define SHOWTRANSACTIONS_H

#include <QDialog>
#include "selectactionmenu.h"

namespace Ui {
class showTransactions;
}

class showTransactions : public QDialog
{
    Q_OBJECT

public:
    explicit showTransactions(QWidget *parent = nullptr);
    ~showTransactions();
    void setShowMyTransactions(const QString &newShowMyTransactions);

private slots:
    void on_nappi_sulje_clicked();

    void on_nappi_kirjaudu_ulos_clicked();
    void timeOut();

private:
    Ui::showTransactions *ui;
    QString showMyTransactions;
    QTimer *ajastinTilitapahtumat;
    MainWindow *etusivu;
    logOut *kirjauduUlosIkkuna;

};

#endif // SHOWTRANSACTIONS_H
