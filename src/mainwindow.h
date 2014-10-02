#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

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

private slots:
    void on_actionNew_Climber_triggered();

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    QSqlTableModel *model;
};
