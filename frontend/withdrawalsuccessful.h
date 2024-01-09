#ifndef WITHDRAWALSUCCESSFUL_H
#define WITHDRAWALSUCCESSFUL_H

#include <QDialog>
#include "selectactionmenu.h"

namespace Ui {
class withdrawalSuccessful;
}

class withdrawalSuccessful : public QDialog
{
    Q_OBJECT

public:
    Ui::withdrawalSuccessful *ui;
    explicit withdrawalSuccessful(QWidget *parent = nullptr);
    ~withdrawalSuccessful();

private slots:
    void on_nappi_sulje_clicked();
    void timeOut();

private:
    //Ui::withdrawalSuccessful *ui;
    QTimer *ajastinNostoOK;
    selectActionMenu *valikkoNostoOK;
};

#endif // WITHDRAWALSUCCESSFUL_H
