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
        query.exec("CREATE TABLE contacts (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40),\
                   email VARCHAR(50), expirationDate DATE, status CHAR(1), PRIMARY KEY (email))");
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
