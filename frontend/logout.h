#ifndef LOGOUT_H
#define LOGOUT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class logOut;
}

class logOut : public QDialog
{
    Q_OBJECT

public:
    explicit logOut(QWidget *parent = nullptr);
    ~logOut();


    void setLogMeOut(const QString &newLogMeOut);

signals:
    void windowShown();

public slots:
    void kaynnistaAjastinLogOut();

private slots:
    void timeOut();

protected:
    void showEvent(QShowEvent *event) override;

private:
    Ui::logOut *ui;
    QString logMeOut;
    QTimer *ajastinLogOut;
    MainWindow *etusivuLogOut;
};

#endif // LOGOUT_H
