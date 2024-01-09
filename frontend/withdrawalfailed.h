#ifndef WITHDRAWALFAILED_H
#define WITHDRAWALFAILED_H

#include <QDialog>
#include "selectactionmenu.h"
#include "selectsum.h"

namespace Ui {
class withdrawalFailed;
}

class withdrawalFailed : public QDialog
{
    Q_OBJECT

public:
    Ui::withdrawalFailed *ui;
    explicit withdrawalFailed(QWidget *parent = nullptr);
    ~withdrawalFailed();
private slots:
    void on_nappi_muuta_summaa_clicked();
    //void on_nappi_sulje_nostotapahtumat_clicked();
    void on_nappi_kirjaudu_ulos_clicked();

    void timeOut();

private:
   //Ui::withdrawalFailed *ui;
    QTimer * ajastinNostoFail;
    selectSum *valitseSumma;
    selectActionMenu * valikkoNostoFail;

    logOut * kirjauduUlosIkkuna;

};

#endif // WITHDRAWALFAILED_H
