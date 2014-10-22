#include "dbmanager.h"

bool DBManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QFileInfo fileInfo("vertsys.db");
    db.setDatabaseName(fileInfo.absoluteFilePath());
    bool status;
    if (!fileInfo.exists())
    {
        status = db.open();
        QSqlQuery query(db);
        qDebug() << "Creating tables" << endl;
        query.exec("CREATE TABLE climber (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40),\
                   email VARCHAR(50), expirationDate DATE, startDate DATE, status CHAR(1), PRIMARY KEY (email))");
        query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC)");
    }
    else
        status = db.open();

    return status;
}

QSqlError DBManager::lastError()
{
    return db.lastError();
}

DBManager::~DBManager()
{
    db.close();
}
