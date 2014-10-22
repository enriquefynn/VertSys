#pragma once

#include <QObject>
#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QtDebug>
#include <QList>
#include <QVBoxLayout>

#include "climbermodel.h"
#include "climber.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);
    
signals:
    void updateClimberInfo(Climber *&climber);
    void updateActivateOption(int);

public slots:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);
    void removeClimber();
    void updateIdx();
    void toggleActivity();
    void updateClimberInfo();
    void commitExpirationDate(QDate date);

private:
    void setupTabs();
    void setupModel();
    ClimberModel *model;
    QTableView *tableView;
    QSortFilterProxyModel *proxyTextModel;
    QSortFilterProxyModel *proxyModel;
    int selectedRow();
};
