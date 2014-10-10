#pragma once

#include <QSqlTableModel>
#include <QDate>

class MyModel : public QSqlTableModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent);
    QVariant data(const QModelIndex &index, int role) const;
    bool insertClimber(QString &name, QString &phone, QString &address, QString &email, QDate &expirationDate, QDate &startDate);
    void update();
};
