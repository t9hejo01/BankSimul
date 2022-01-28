#include "dllmysql.h"

#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlQueryModel>
#include <QSqlTableModel>

QSqlDatabase DLLMySQL::db;

DLLMySQL::DLLMySQL()
{
    if(createConnection())
        query = new QSqlQuery;
}

DLLMySQL::~DLLMySQL()
{
    delete query;
    query = nullptr;
}

// Yhdistä tietokantaan
bool DLLMySQL::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("mysli.oamk.fi");

    db.setDatabaseName("opisk_t9laju04");
    db.setUserName("t9laju04");
    db.setPassword("W45GNJgDGhwMX6YW");

    if (!db.open())
    {
        QMessageBox::critical(0, qApp -> tr("Cannot open database"),
        qApp -> tr("Unable to establish a database connection.\n"),
        QMessageBox::Cancel);
        qDebug() << "Yhteytta ei voitu muodostaa" << endl;

        return false;
    }

    return true;
}

// Tarkista löytyykö kortti tietokannasta
bool DLLMySQL::verifyCardKey(QString key)
{
    query->prepare("SELECT * FROM Card WHERE card_id = :key");
    query->bindValue(":key", key);

    query->exec();
    query->first();

    return (query->size() > 0);
}

// Tarkista että annettu pin-koodi vastaa annetun kortin pin-koodia
QString DLLMySQL::verifyCardPin(QString key, QString pin)
{
    query->prepare("SELECT account_id FROM Card WHERE card_id = :key and pin = :pin");
    query->bindValue(":key", key);
    query->bindValue(":pin", pin);

    query->exec();
    query->first();

    if(query->size() > 0)
        return query->value(0).toString();
    else
        return "ERROR";
}

// Palauta pyydetty tieto annetulta tililtä
QString DLLMySQL::getAccountData(QString accountId, SearchMode mode)
{
    QString returnValue;

    // Tilin käyttäjän nimi
    if(mode == name)
    {
        // Etsi käyttäjän id annetun tilinumeron persuteella
        query->prepare("SELECT user_id FROM Account WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->first();
        int userId = query->value(0).toInt();

        // Etsi käyttäjän nimi id:n perusteella
        query->prepare("SELECT firstname, lastname FROM User WHERE user_id = :user_id");
        query->bindValue(":user_id", userId);
        query->exec();

        query->first();

        returnValue = query->value(0).toString() + " " + query->value(1).toString();
    }
    // Tilin saldo
    else if(mode == saldo)
    {
        // Etsi saldo annetun tilinumeron perusteella
        query->prepare("SELECT saldo FROM Account WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->first();

        returnValue = query->value(0).toString();
    }
    // Tilin taphatumat
    else if(mode == activity)
    {
        // Etsi kaikki tapahtumat annetulta tilitä
        query->prepare("SELECT description FROM Activity WHERE account_id = :account_id");
        query->bindValue(":account_id", accountId);
        query->exec();

        query->last();

        returnValue = "";

        // Liitä kaikki tapahtumat yhteen
        do
            returnValue += query->value(0).toString() + "\n\n";
        while(query->previous());
    }

    return returnValue;
}

// Muuta annetun tilin saldoa
bool DLLMySQL::editSaldo(QString accountId, int amount)
{
    // Keskeytä jos annettu määrä on 0 tai suurempi kuin tilin saldo
    if(amount == 0 || (amount < 0 && -amount > getAccountData(accountId, saldo).toFloat()))
        return false;

    // Muuta saldon arvoa tietokannassa
    query->prepare("UPDATE Account SET saldo = saldo + :amount WHERE account_id = :account_id");
    query->bindValue(":amount", amount);
    query->bindValue(":account_id", accountId);

    // Palauta "true" tai "false" riippuuen onnistuiko saldon muuttaminen
    if(!query->exec())
        return false;
    else
    {
        // Kirjaa tapahtuma
        addActivity(accountId, amount);

        return true;
    }
}

// Lisää tapahtuma tietokantaan
void DLLMySQL::addActivity(QString accountId, int amount)
{
    // Tapahtuman päivämäärä ja kellonaika
    QString activity = QDateTime().currentDateTime().toString("dd.MM.yyyy | HH:mm") + " | ";

    // Määritä onko tapahtuma nosto vai talletus
    if(amount < 0)
        activity += "Nosto: " + QString().setNum(-amount) + " €";
    else
        activity += "Talletus: " + QString().setNum(amount) + " €";

    // Etsi seuraava vapaa primary key
    query->exec("SELECT activity_id FROM Activity;");
    query->last();
    int nextId = query->size();

    // Tallenna tapahtuma tietokantaan
    query->prepare("INSERT INTO Activity VALUES(:activity_id, :account_Id, :activity);");
    query->bindValue(":activity_id", nextId);
    query->bindValue(":account_Id", accountId);
    query->bindValue(":activity", activity);

    query->exec();
}
