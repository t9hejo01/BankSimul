#ifndef DLLMYSQL_H
#define DLLMYSQL_H

#include "DLLMySQL_global.h"
#include <QMessageBox>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtWidgets>
#include <QWidget>
#include <QSqlTableModel>
#include <QtSql>
#include <QString>
#include <QDateTime>

enum SearchMode
{
    name,
    saldo,
    activity
};

class DLLMySQL : public QObject
{
    Q_OBJECT

public:
    DLLMySQL();
    ~DLLMySQL();

    static bool createConnection();
    void getValuesFromModel(QSqlTableModel *model);

    QString naytaSaldo(QString pinKoodi);
    bool verifyCardKey(QString key);
    QString verifyCardPin(QString key, QString pin);
    QString getAccountData(QString accountId, SearchMode mode);
    bool editSaldo(QString accountID, int amount);
    void addActivity(QString accountID, int amount);

private:
    static QSqlDatabase db;
    QSqlQuery *query;
};

#endif // DLLMYSQL_H
