#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(4);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setAlignment(Qt::AlignCenter);
}

Dialog::~Dialog()
{
    delete ui;
    ui = nullptr;
}

void Dialog::on_PushButton_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void Dialog::on_PushButton_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void Dialog::on_PushButton_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void Dialog::on_PushButton_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void Dialog::on_PushButton_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void Dialog::on_PushButton_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void Dialog::on_PushButton_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void Dialog::on_PushButton_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void Dialog::on_PushButton_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void Dialog::on_PushButton_Reset_clicked()
{
    ui->lineEdit->clear();

}

void Dialog::on_PushButton_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void Dialog::on_PushButton_OK_clicked()
{
    pincode = ui->lineEdit->text();
    ui->lineEdit->clear();

    emit sendPin(pincode);
}
