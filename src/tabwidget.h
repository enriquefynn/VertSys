#pragma once

#include <QObject>
#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QtDebug>
#include <QList>
#include <QVBoxLayout>

#include "climbermodel.h"
#include "paymentmodel.h"
#include "climber.h"
#include "vertsys.h"
#include "registeruser.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = 0);
    
signals:
    void updateClimberInfo(Climber *&climber);
    void updateActivateOption(int);
    void editClimberWindow(int, Climber*);

public slots:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);
    void removeClimber();
    void editClimber(const QModelIndex&);
    void editClimberInDB(int row, Climber *&climber);
    void updateIdx();
    void toggleActivity();
    void updateClimberInfo();
    void setPayment(QDate date, double value);

private:
    void setupTabs();
    void setupModel();
    ClimberModel *climberModel;
    PaymentModel *paymentModel;
    QTableView *tableView;
    QSortFilterProxyModel *proxyTextModel;
    QSortFilterProxyModel *proxyModel;
    int selectedRow();
};
