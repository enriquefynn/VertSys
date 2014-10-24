/* CHANGES IN DB
 * enriquefynn: First model                     -v0
 * thadeuk: Added payment table                 -v1
 * enriquefynn: Added observations in climber   -v2
 */

#include <QStringList>

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
                   email VARCHAR(50), expirationDate DATE, startDate DATE, status CHAR(1), observations TEXT, PRIMARY KEY (email))");
        query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
    }
    else
    {
        status = db.open();
        QSqlQuery query(db);
        //Check if db is not v1
        if (!db.tables().contains("payment"))
        {
            qDebug() << "Updating to DB v1" << endl;
            query.exec("CREATE TABLE payment (id INTEGER PRIMARY KEY, email TEXT, paymentDate DATE, expirationDate DATE, value NUMERIC, FOREIGN KEY(email) REFERENCES climber(email))");
        }
        //Check if db is not v2
        if (db.record("climber").indexOf("observations") == -1)
        {
            qDebug() << "Updating to DB v2" << endl;
            query.exec("ALTER TABLE climber ADD COLUMN observations TEXT");
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
