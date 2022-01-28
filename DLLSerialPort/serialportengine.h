#ifndef SERIALPORTENGINE_H
#define SERIALPORTENGINE_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QTextCodec>
#include <QDebug>

class SerialPortEngine : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortEngine(QObject *parent = nullptr);
    ~SerialPortEngine();
    void openConnection();

private:
    QSerialPort *serial;
    QByteArray byteArray;
    QString keyString;

signals:
    void sendKey(QString);

private slots:
    void receiveSerial();
};

#endif // SERIALPORTENGINE_H
