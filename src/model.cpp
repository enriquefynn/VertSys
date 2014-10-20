#include <QBrush>
#include <QtDebug>
#include <QSqlRecord>
#include <QTimer>
#include "model.h"

MyModel::MyModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 4)
    {
        QDate value = QDate::fromString(QSqlQueryModel::data(index, Qt::DisplayRole).toString(), "yyyy-MM-dd");
        switch(role)
        {
            case Qt::DisplayRole:
                return value;

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
    if (role == Qt::DisplayRole)
        return QSqlTableModel::data(index,role);
    return QVariant();
}

bool MyModel::insertClimber(Climber *&climber)
{
    QSqlRecord rec = record();
    rec.setValue("name", climber->getName());
    rec.setValue("phone", climber->getPhone());
    rec.setValue("address", climber->getAddress());
    rec.setValue("email", climber->getEmail());
    rec.setValue("expirationDate", climber->getExpirationDate());
    rec.setValue("startDate", climber->getStartDate());
    rec.setValue("status", climber->getStatus());
    bool ret = insertRecord(-1, rec);
    submitAll();
    emit layoutChanged();
    qDebug() << "INSERTED: " << ret << endl;
    return ret;
}

bool MyModel::removeClimber(int row)
{
    bool ret = removeRows(row, 1);
    submitAll();
    emit layoutChanged();
    return ret;
}

void MyModel::toggleActivity(int row)
{
    if (index(row, 6).data() == "D")
        setData(index(row, 6), "A");
    else if (index(row, 6).data() == "A")
        setData(index(row, 6), "I");
    else
        setData(index(row, 6), "A");
    submitAll();
    emit layoutChanged();
}

Climber * MyModel::getClimber(int row)
{
    QString name, phone, address, email, status;
    QDate expirationDate, startDate;

    name = index(row, 0).data().toString();
    phone = index(row, 1).data().toString();
    address = index(row, 2).data().toString();
    email = index(row, 3).data().toString();
    expirationDate = index(row, 4).data().toDate();
    startDate = index(row, 5).data().toDate();
    status = index(row, 6).data().toString();
    return new Climber(name, phone, address, email, expirationDate, startDate, status);
}
