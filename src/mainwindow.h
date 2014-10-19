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

public slots:
    void insertClimber(Climber *&climber);
    void rowSelected(QModelIndex x, QModelIndex y);

signals:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);
    void removeClimber();

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    //MyModel *model;
    //QTableView *tableView;
    //QSortFilterProxyModel *proxyModel;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
