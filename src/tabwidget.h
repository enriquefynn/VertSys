#pragma once

#include <QObject>
#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QtDebug>
#include <QList>
#include <QVBoxLayout>

#include "model.h"
#include "climber.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);

private:
    void setupTabs();
    void setupModel();
    MyModel *model;
    QTableView *tableView;
    QSortFilterProxyModel *proxyTextModel;
    QSortFilterProxyModel *proxyModel;
};
