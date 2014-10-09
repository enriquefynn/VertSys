#include "dbmanager.h"

bool DBManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QFileInfo fileInfo("vertsys.db");
    db.setDatabaseName(fileInfo.absoluteFilePath());
    if (!fileInfo.exists())
    {
        QSqlQuery query(db);
        query.exec("CREATE TABLE contacts (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40))");
    }
    return db.open();
}

QSqlError DBManager::lastError()
{
    return db.lastError();
}

DBManager::~DBManager()
{
    db.close();
}
