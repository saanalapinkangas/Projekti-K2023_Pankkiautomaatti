#include "dll_rfid.h"

DLL_rfid::DLL_rfid(QObject *parent) : QObject{parent}
{
    serialport = new QSerialPort;
    serialport ->setPortName("COM3"); // windows avain + x -> laitehallinta -> näytä piilotetut laitteet -> portit (varmista että lukijan nappia painettu)
    serialport->setBaudRate(QSerialPort::Baud9600);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setParity(QSerialPort::NoParity);
    serialport->setStopBits(QSerialPort::OneStop);

    connect(serialport, &QSerialPort::readyRead, this, &DLL_rfid::returnCardID);

    /* if(serialport->open(QIODevice::ReadWrite)) {
        qDebug() << serialport->errorString();
    } else {
        qDebug() << "Serial open ok";
    }*/
}

void DLL_rfid::openSerialPort()
{
    serialport->open(QIODevice::ReadWrite);
}


void DLL_rfid::returnCardID()
{
    //kutsu serial-objektin metodia readAll, joka palauttaa QByteArrayna kortin id:n
    QByteArray data = serialport->readAll();
    QByteArray newData = data.mid(3, data.length() - 4).trimmed();  //aloittaa toiston kolmannesta merkistä, lopettaa toiseksi viimeiseen
    qDebug() << "dll returnCardID, vanha data: " << data;
    qDebug() << "dll returnCardID, trimmattu data: " << newData;
    emit cardRead(newData);
    //QString cardData = QString::fromLatin1(data); //QByteAttayn käänt. stringiksi (vaihda myös cardRead > (QString cardData)
}

DLL_rfid::~DLL_rfid()
{
    delete serialport;
}

/*void DLL_rfid::startReading()
{
    connect(serialport, &QSerialPort::readyRead, this, DLL_rfid::returnCardID());
    qDebug() << "startReading";
}*/
