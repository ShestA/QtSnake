#include "sqlwrap.hpp"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QObject>

void SQLwrap::OpenDB(QString host, QString username, QString pass, QString dbname)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("SNAKESQL");
    db.setHostName(host);
    db.setUserName(username);
    db.setPassword(pass);
    db.setDatabaseName(dbname);
    if (!db.open()){
        if (db.lastError().isValid()) {
            QWidget *test = new QWidget();
            QPalette pallette;
            pallette.setColor(QPalette::Background, Qt::black);
            QMessageBox *error = new QMessageBox;
            error->setPalette(pallette);
            QString text = db.lastError().text();
            error->about(test, QObject::tr("DB Error"), QObject::tr(qPrintable(text)));
        }
    }
}

void SQLwrap::closeDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}

bool SQLwrap::isConValid()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen())
    {
        return true;
    }
    return false;
}

bool SQLwrap::isStructValid()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.tables().contains( QString("field"))) {
        return true;
    }
    return false;
}

QString SQLwrap::getError()
{
    QSqlDatabase db = QSqlDatabase::database();
    if(db.lastError().isValid())
    {
        return QString(db.lastError().text());
    }
    return QString("No Errors");
}

void SQLwrap::deployTable()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!this->isStructValid())
    {
        QSqlQuery query;

        query.exec("DROP SEQUENCE XXX IF EXISTS;");

        query.exec("CREATE SEQUENCE XXX START 1;");

        query.exec("DROP TABLE IF EXISTS field");

        query.exec("CREATE TABLE field ();");
    }
}

void SQLwrap::sendData(QList<QList<bool>> data)
{
    QSqlDatabase db = QSqlDatabase::database();
    //QDateTime * timestamp = new QDateTime;
    QSqlQuery query;
    query.exec("INSERT INTO field ()");
}
