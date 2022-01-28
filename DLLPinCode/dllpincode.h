#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include <QWidget>
#include "DLLPinCode_global.h"
#include "dialog.h"

class DLLPINCODE_EXPORT DLLPinCode : public QWidget
{

    Q_OBJECT
public:
    DLLPinCode();
    ~DLLPinCode();
    void toggleDialog(bool);

private:
    Dialog *objectDLLPinCodeEngine;

private slots:
    void receivePin(QString);


signals:
    void returnPin(QString);
};



#endif // DLLPINCODE_H
