#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>
#include <QDebug>

#include "DLLSerialPort_global.h"
#include "serialportengine.h"

class DLLSERIALPORT_EXPORT DLLSerialPort: public QObject
{
    Q_OBJECT
public:
    DLLSerialPort();
    ~DLLSerialPort();

private:
    SerialPortEngine *serialEngine;

signals:
    void returnKey(QString);

private slots:
    void receiveKey(QString);
};

#endif // DLLSERIALPORT_H
