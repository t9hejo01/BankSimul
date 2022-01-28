#include "dllserialport.h"

DLLSerialPort::DLLSerialPort()
{
    // Create the engine.
    serialEngine = new SerialPortEngine();

    // Receive the key from the engine after it's been cleaned.
    connect(serialEngine, SIGNAL(sendKey(QString)), this, SLOT(receiveKey(QString)));

    // Try to open a connection to serial.
    serialEngine->openConnection();
}

DLLSerialPort::~DLLSerialPort()
{
    delete serialEngine;
    serialEngine = nullptr;
}

void DLLSerialPort::receiveKey(QString keyString)
{
    // Send the key to be read by other slots.
    emit returnKey(keyString);
}
