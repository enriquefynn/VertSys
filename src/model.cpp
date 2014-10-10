#include <QBrush>
#include <QtDebug>
#include "model.h"

MyModel::MyModel(QObject *parent) :
    QSqlTableModel(parent)
{
}

void MyModel::update()
{
    emit this->layoutChanged();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (index.column() == 4)
    {
        QVariant value = QSqlQueryModel::data(index, Qt::DisplayRole);
        switch(role)
        {
            case Qt::BackgroundRole:
                QDate today = QDate::currentDate();
                qDebug() << "Data: " << QDate::fromString(value.toString(), "yyyy-MM-dd") << endl;
                if (today >= QDate::fromString(value.toString(), "yyyy-MM-dd"))
                {
                    QBrush redBackground(Qt::red);
                    return redBackground;
                }
                break;
        }
    }
    return QSqlTableModel::data(index,role);
}
