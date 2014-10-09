#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QTableView>
#include <QSortFilterProxyModel>

#include "registeruser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateLayout();

private slots:
    void on_actionNew_Climber_triggered();
    void on_lineEdit_search_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    QSqlTableModel *model;
    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;
};
