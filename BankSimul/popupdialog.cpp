#include "popupdialog.h"
#include "ui_popupdialog.h"

PopUpDialog::PopUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUpDialog)
{
    ui->setupUi(this);
}

// Avaa ikkuna tietyssä tilassa
void PopUpDialog::avaa(PopUpMode mode)
{
    if(mode == nosto)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_onnistui->setText("Nosto onnistui!");
    }
    else if(mode == talletus)
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->label_onnistui->setText("Talletus onnistui!");
    }
    else if(mode == epaonnistui)
        ui->stackedWidget->setCurrentIndex(1);
    else if(mode == kirjaudu)
        ui->stackedWidget->setCurrentIndex(2);

    this->show();
}

PopUpDialog::~PopUpDialog()
{
    delete ui;
    ui = nullptr;
}

// Siirry etusivulle
void PopUpDialog::on_pushButton_etusivu_clicked()
{
    emit siirryEtusivu();
    this->close();
}

// Siirry tilitietoihin
void PopUpDialog::on_pushButton_tiedot_clicked()
{
    emit siirryTiedot();
    this->close();
}


// Sulje ikkuna
void PopUpDialog::on_pushButton_ok_clicked()
{
    this->close();
}

void PopUpDialog::on_pushButton_ei_clicked()
{
    this->close();
}


// Kirjaudu ulos
void PopUpDialog::on_pushButton_kylla_clicked()
{
    emit kirjauduUlos();
    this->close();
}
