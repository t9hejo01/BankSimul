#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "popupdialog.h"

#include "../DLLSerialPort/dllserialport.h"
#include "../DLLPinCode/dllpincode.h"
#include "../DLLMySQL/dllmysql.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateAccountData();
    void withdraw(int amount);
    void resetTimer();

private slots:
    void getKeyFromSerial(QString);
    void getPin(QString);

    void on_pushButton_nosta_clicked();
    void on_pushButton_talleta_clicked();
    void on_pushButton_tiedot_clicked();

    void on_pushButton_kirjauduUlos_clicked();
    void logOut();

    void on_pushButton_takaisin_1_clicked();
    void on_pushButton_takaisin_2_clicked();
    void on_pushButton_takaisin_3_clicked();

    void on_pushButton_hyvaksy_talletus_clicked();

    void on_pushButton_nosta_20_clicked();
    void on_pushButton_nosta_50_clicked();
    void on_pushButton_nosta_100_clicked();
    void on_pushButton_nosta_150_clicked();
    void on_pushButton_nosta_200_clicked();
    void on_pushButton_nosta_250_clicked();

    void on_pushButton_skipKortti_clicked();

    void on_timeout();

private:
    Ui::MainWindow *ui;
    DLLSerialPort *objectSerialPort;
    DLLPinCode *objectPinCode;
    DLLMySQL *objectMySQL;
    PopUpDialog *objectPopUpDialog;
    QTimer *objectTimer;

    QString cardKey;
    QString accountId;
};
#endif // MAINWINDOW_H
