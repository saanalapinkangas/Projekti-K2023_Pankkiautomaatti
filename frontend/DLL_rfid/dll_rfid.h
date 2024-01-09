#ifndef DLL_RFID_H
#define DLL_RFID_H

#include "DLL_rfid_global.h"
//#include <QDialog>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
//#include <QObject>

class DLL_RFID_EXPORT DLL_rfid : public QObject
{
    Q_OBJECT

public:
    DLL_rfid(QObject *parent);
    ~DLL_rfid();
    void openSerialPort();   // avataan serialport
    // void startReading();
    void returnCardID();

signals:
    void cardRead(QByteArray data);

private:
    QSerialPort * serialport;   // luodaan olio serialportille
};

#endif // DLL_RFID_H
