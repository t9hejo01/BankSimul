#include "dllpincode.h"
#include "ui_dialog.h"
#include <QDesktopWidget>

DLLPinCode::DLLPinCode()
{
   objectDLLPinCodeEngine = new Dialog;
   connect(objectDLLPinCodeEngine, SIGNAL(sendPin(QString)), this, SLOT(receivePin(QString)));

}

DLLPinCode::~DLLPinCode()
{
    delete objectDLLPinCodeEngine;
    objectDLLPinCodeEngine = nullptr;
}

void DLLPinCode::toggleDialog(bool showDialog)
{
    if(showDialog)
        objectDLLPinCodeEngine->show();
    else
        objectDLLPinCodeEngine->close();
}

void DLLPinCode::receivePin(QString receivedPin)
{
    emit returnPin(receivedPin);
}
