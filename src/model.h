#pragma once

#include <QSqlTableModel>
#include <QDate>

#include "climber.h"

class MyModel : public QSqlTableModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent);
    QVariant data(const QModelIndex &index, int role) const;
    bool insertClimber(Climber *&climber);
    void update();
};
