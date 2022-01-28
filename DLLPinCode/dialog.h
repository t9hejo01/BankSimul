#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QApplication>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{

    Q_OBJECT
public:
     Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_PushButton_1_clicked();

    void on_PushButton_2_clicked();

    void on_PushButton_3_clicked();

    void on_PushButton_4_clicked();

    void on_PushButton_5_clicked();

    void on_PushButton_6_clicked();

    void on_PushButton_7_clicked();

    void on_PushButton_8_clicked();

    void on_PushButton_9_clicked();

    void on_PushButton_Reset_clicked();

    void on_PushButton_0_clicked();

    void on_PushButton_OK_clicked();

private:
    QString pincode;
    Ui::Dialog *ui;



signals:
    void sendPin(QString);
};

#endif // DIALOG_H
