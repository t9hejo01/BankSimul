#include "serialportengine.h"

SerialPortEngine::SerialPortEngine(QObject *parent) : QObject(parent)
{
    // Create and define settings for serial.
    serial = new QSerialPort(this);
    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Receive a signal from serial whenever it's ready to be read.
    connect(serial, SIGNAL(readyRead()), this, SLOT(receiveSerial()));
}

SerialPortEngine::~SerialPortEngine()
{
    // Close serial.
    serial->close();

    delete serial;
    serial = nullptr;
}

void SerialPortEngine::openConnection()
{
    // Try to open a connection to serial.
    serial->open(QIODevice::ReadOnly);

    // Clear serial.
    serial->clear(QSerialPort::AllDirections);
}

void SerialPortEngine::receiveSerial()
{
    // Read serial, and save whatever was read to a byte array.
    byteArray = serial->readAll();

    // Convert byte array into string.
    keyString = QTextCodec::codecForMib(106)->toUnicode(byteArray);

    // Remove unnecessary parts from the string, leaving only the key.
    keyString.remove("\r\n-");
    keyString.remove("\r\n>");

    // Send the key to DLLSerialPort.
    emit sendKey(keyString);
}
