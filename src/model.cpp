#include <QBrush>
#include <QtDebug>
#include <QSqlRecord>

#include "model.h"

MyModel::MyModel(QObject *parent) :
    QSqlTableModel(parent)
{
}

void MyModel::update()
{
    qDebug() << "Updating..." << endl;
    emit layoutChanged();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 4)
    {
        QDate value = QDate::fromString(QSqlQueryModel::data(index, Qt::DisplayRole).toString(), "yyyy-MM-dd");
        switch(role)
        {
            //case Qt::DisplayRole:
            //    return value.toString("dd/MM/yyyy");

            case Qt::BackgroundRole:
                QDate today = QDate::currentDate();
                if (today >= value)
                {
                    QBrush redBackground(Qt::red);
                    return redBackground;
                }
                break;
        }
    }
    return QSqlTableModel::data(index,role);
}

bool MyModel::insertClimber(QString &name, QString &phone, QString &address, QString &email, QDate &expirationDate, QDate &startDate)
{
    QSqlRecord rec = record();
    rec.setValue("name", name);
    rec.setValue("phone", phone);
    rec.setValue("address", address);
    rec.setValue("email", email);
    rec.setValue("expirationDate", expirationDate);
    rec.setValue("startDate", startDate);
    rec.setValue("status", "O");
    bool ret = insertRecord(-1, rec);

    return ret;
}
