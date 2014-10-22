#pragma once

#include <QSqlTableModel>
#include <QDate>

#include "climber.h"

class ClimberModel : public QSqlTableModel
{
    Q_OBJECT
public:
    ClimberModel(QObject *parent);
    QVariant data(const QModelIndex &index, int role) const;
    bool insertClimber(Climber *&climber);
    bool removeClimber(int row);
    void toggleActivity(int row);
    Climber *& getClimber(int row);
    bool updateExpirationDate(int row, QDate date);

private:
    Climber *c;
};
