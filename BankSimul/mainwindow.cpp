#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objectMySQL = new DLLMySQL;

    objectSerialPort = new DLLSerialPort;
    connect(objectSerialPort, SIGNAL(returnKey(QString)), this, SLOT(getKeyFromSerial(QString)));

    objectPinCode = new DLLPinCode;
    connect(objectPinCode, SIGNAL(returnPin(QString)), this, SLOT(getPin(QString)));

    objectPopUpDialog = new PopUpDialog;
    connect(objectPopUpDialog, SIGNAL(siirryEtusivu()), this, SLOT(on_pushButton_takaisin_1_clicked()));
    connect(objectPopUpDialog, SIGNAL(siirryTiedot()), this, SLOT(on_pushButton_tiedot_clicked()));
    connect(objectPopUpDialog, SIGNAL(kirjauduUlos()), this, SLOT(logOut()));

    objectTimer = new QTimer;
    objectTimer->setInterval(30000);
    objectTimer->setSingleShot(true);
    connect(objectTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    // Alusta muuttujat
    cardKey = "";
    accountId = "";
}

MainWindow::~MainWindow()
{
    delete ui;
    ui = nullptr;

    delete objectSerialPort;
    objectSerialPort = nullptr;

    delete objectPinCode;
    objectPinCode = nullptr;

    delete objectMySQL;
    objectMySQL = nullptr;

    delete objectPopUpDialog;
    objectPopUpDialog = nullptr;

    delete objectTimer;
    objectTimer = nullptr;
}

// Päivitä tilin tiedot käyttöliittymään
void MainWindow::updateAccountData()
{
   ui->label_tervetuloa->setText("Tervetuloa " + objectMySQL->getAccountData(accountId, name));
   ui->label_saldo->setText("Saldo: " + objectMySQL->getAccountData(accountId, saldo) + " €");
   ui->label_tilinumero->setText("Tili: " + accountId);

   ui->textBrowser_tapahtumat->setText(objectMySQL->getAccountData(accountId, activity));
}

// Ota vastaan SerialPortDLL:n lähettämä kortin koodi
void MainWindow::getKeyFromSerial(QString key)
{
    cardKey = key;

    // Avaa ikkuna jossa käyttäjä antaa pin-koodin JOS kortti löytyy tietokannasta
    if(ui->stackedWidget->currentIndex() == 0)
    {
        if(objectMySQL->verifyCardKey(cardKey))
            objectPinCode->toggleDialog(true);
    }
}

// Ota vastaan PinCodeDLL:n lähettämä pin ja kirjaudu sisään jos pin ja kortti täsmäävät
void MainWindow::getPin(QString pin)
{
    accountId = objectMySQL->verifyCardPin(cardKey, pin);

    if(accountId != "ERROR")
    {
        objectPinCode->toggleDialog(false);

        updateAccountData();
        ui->stackedWidget->setCurrentIndex(1);

        // Aloita ajastus
        resetTimer();
    }
}

// Siiry sivulle "Nosta"
void MainWindow::on_pushButton_nosta_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    resetTimer();
}

// Siirry sivulle "Talleta"
void MainWindow::on_pushButton_talleta_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

    resetTimer();
}

// Siirry sivulle "Tiedot"
void MainWindow::on_pushButton_tiedot_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    resetTimer();
}

// Varmista ulos kirjautuminen
void MainWindow::on_pushButton_kirjauduUlos_clicked()
{
    objectPopUpDialog->avaa(kirjaudu);

    resetTimer();
}

// Kirjaudu ulos
void MainWindow::logOut()
{
    accountId = "";
    ui->stackedWidget->setCurrentIndex(0);
}


// Palaa etusivulle
void MainWindow::on_pushButton_takaisin_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    resetTimer();
}

void MainWindow::on_pushButton_takaisin_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    resetTimer();
}

void MainWindow::on_pushButton_takaisin_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

    resetTimer();
}


// Talleta tilille annettu määrä
void MainWindow::on_pushButton_hyvaksy_talletus_clicked()
{
    int amount = ui->lineEdit_maara_talletus->text().toInt();

    if(objectMySQL->editSaldo(accountId, amount))
    {
        updateAccountData();
        objectPopUpDialog->avaa(talletus);
    }
    else
        objectPopUpDialog->avaa(epaonnistui);

    ui->lineEdit_maara_talletus->setText("");

    resetTimer();
}

// Nosta tilitlä annettu määrä
void MainWindow::withdraw(int amount)
{
    if(objectMySQL->editSaldo(accountId, -amount))
    {
        updateAccountData();
        objectPopUpDialog->avaa(nosto);
    }
    else
        objectPopUpDialog->avaa(epaonnistui);

    resetTimer();
}


// Valitse nostettava määrä
void MainWindow::on_pushButton_nosta_20_clicked()
{
    withdraw(20);
}

void MainWindow::on_pushButton_nosta_50_clicked()
{
    withdraw(50);
}

void MainWindow::on_pushButton_nosta_100_clicked()
{
    withdraw(100);
}

void MainWindow::on_pushButton_nosta_150_clicked()
{
    withdraw(150);
}

void MainWindow::on_pushButton_nosta_200_clicked()
{
    withdraw(200);
}

void MainWindow::on_pushButton_nosta_250_clicked()
{
    withdraw(250);
}


// Kirjaudu sisään ilman korttia
void MainWindow::on_pushButton_skipKortti_clicked()
{
    getKeyFromSerial(ui->lineEdit_skip->text());
}

// Resetoi ajastin ja aloita ajastus
void MainWindow::resetTimer()
{
    objectTimer->stop();
    objectTimer->start();
}

// Kirjaudu ulos jos käyttäjä ei tee mitään 30 sekunnin sisällä
void MainWindow::on_timeout()
{
    logOut();
}
