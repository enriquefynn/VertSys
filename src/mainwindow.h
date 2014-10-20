#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QTableView>
#include <QSortFilterProxyModel>

#include "registeruser.h"
#include "model.h"
#include "climber.h"
#include "payment.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    friend class TabWidget;
    Q_OBJECT

private slots:
    void on_actionNew_Climber_triggered();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_actionRemove_Climber_triggered();
    void on_actionToggleActivity_Climber_triggered();

    void on_actionPay_Climber_triggered();

public slots:
    void insertClimber(Climber *&climber);
    void rowSelected(QModelIndex x, QModelIndex y);
    void recvClimberInfo(Climber *&climber);
    void setExpirationDate(QDate date);
    void updateActivateOption(int idx);

signals:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);
    void removeClimber();
    void toggleActivity();
    void updateClimberInfo();
    void updateClimberInfo(Climber *&climber);
    void commitExpirationDate(QDate date);

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    Payment *payment;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
