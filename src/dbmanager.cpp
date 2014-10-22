/* CHANGES IN DB
 * enriquefynn: First model     -v0
 * thadeuk: Added payment table -v1
 */

#include <QStringList>

#include "dbmanager.h"

bool DBManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QFileInfo fileInfo("vertsys.db");
    db.setDatabaseName(fileInfo.absoluteFilePath());
    bool status = db.open();
    QSqlQuery query(db);
    if (!fileInfo.exists())
    {
        qDebug() << "Creating tables" << endl;
        query.exec("CREATE TABLE climber (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40),\
                   email VARCHAR(50), expirationDate DATE, startDate DATE, status CHAR(1), PRIMARY KEY (email))");
        query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
    }
    else
    {
        //Check if db is not v1
        if (!db.tables().contains("payment"))
        {
            qDebug() << "Updating to DB v1" << endl;
            query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
        }
    }
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
