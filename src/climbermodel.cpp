#include <QBrush>
#include <QtDebug>
#include <QSqlRecord>
#include <QTimer>
#include "climbermodel.h"

ClimberModel::ClimberModel(QObject *parent) :
    QSqlTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnFieldChange);
}

QVariant ClimberModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == VertSys::expirationDate)
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

bool ClimberModel::insertClimber(Climber *&climber)
{
    QSqlRecord rec = record();
    rec.setValue("name", climber->getName());
    rec.setValue("phone", climber->getPhone());
    rec.setValue("address", climber->getAddress());
    rec.setValue("email", climber->getEmail());
    rec.setValue("expirationDate", climber->getExpirationDate());
    rec.setValue("startDate", climber->getStartDate());
    rec.setValue("status", climber->getStatus());
    rec.setValue("observations", climber->getObservations());

    bool ret = insertRecord(-1, rec);
    submitAll();
    return ret;
}

bool ClimberModel::removeClimber(int row)
{
    bool ret = removeRows(row, 1);
    submitAll();
    return ret;
}

void ClimberModel::toggleActivity(int row)
{
    if (index(row, VertSys::status).data() == "D")
        setData(index(row, VertSys::status), "A");
    else
        setData(index(row, VertSys::status), "D");
    submitAll();
}

bool ClimberModel::updateExpirationDate(int row, QDate date)
{
    return setData(index(row, VertSys::expirationDate), date);
}

Climber *& ClimberModel::getClimber(int row)
{
    QString name, phone, address, email, status, observations;
    QDate expirationDate, startDate;

    name = index(row, VertSys::name).data().toString();
    phone = index(row, VertSys::phone).data().toString();
    address = index(row, VertSys::address).data().toString();
    email = index(row, VertSys::email).data().toString();
    expirationDate = index(row, VertSys::expirationDate).data().toDate();
    startDate = index(row, VertSys::startDate).data().toDate();
    status = index(row, VertSys::status).data().toString();
    observations = index(row, VertSys::observations).data().toString();

    c = new Climber(name, phone, address, email, expirationDate, startDate, status, observations);
    return c;
}
