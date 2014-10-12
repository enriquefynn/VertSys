#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QTableView>
#include <QSortFilterProxyModel>

#include "registeruser.h"
#include "model.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    inline MyModel* getModel(){return model;}
    inline QSortFilterProxyModel* getProxyModel(){return proxyModel;}
private slots:
    void on_actionNew_Climber_triggered();
    void on_lineEdit_search_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    MyModel *model;
    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;
};
