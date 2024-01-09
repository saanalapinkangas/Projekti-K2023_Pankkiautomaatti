#ifndef PINUI_H
#define PINUI_H

#include <QDialog>
#include "pinUIDLL_global.h"

namespace Ui {
class pinUI;
}

class PINUIDLL_EXPORT pinUI : public QDialog
{
    Q_OBJECT

public:
    explicit pinUI(QWidget *parent = nullptr);
    ~pinUI();
signals:
    //void sendPin(short);
    void sendPin (QByteArray);

private slots:
    void clickHandler();
    void clickHandler2();

private:
    Ui::pinUI *ui;
};

#endif // PINUI_H
