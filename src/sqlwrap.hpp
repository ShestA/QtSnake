#ifndef SQLWRAP_H
#define SQLWRAP_H

#include <QString>
#include <QList>
#include <QSql>
#include <QPalette>


class SQLwrap
{
    public:
        void OpenDB(QString hostname, QString username, QString password, QString dbname);
        void closeDB();

        bool isConValid();
        bool isStructValid();
        QString getError();
        void deployTable();
        void sendData(QList<QList<bool>> data);
        QPalette pallett;
};

#endif // SQLWRAP_H
