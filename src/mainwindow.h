#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QTableView>
#include <QFileDialog>

#include "registeruser.h"
#include "edituser.h"
#include "climber.h"
#include "paymentwindow.h"
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
    void on_actionExport_triggered();
    void on_actionImport_triggered();

public slots:
    void insertClimber(Climber *&climber);
    void editClimber(int row, Climber *&climber);
    void rowSelected(QModelIndex x, QModelIndex y);
    void recvClimberInfo(Climber *&climber);
    void updateActivateOption(int idx);
    void displayClimberInfo(int, Climber*);

signals:
    void updateFilter(QString str);
    void insertClimberInDB(Climber *&climber);
    void editClimberInDB(int row, Climber *&climber);
    void removeClimber();
    void toggleActivity();
    void updateClimberInfo();
    void updateClimberInfo(Climber *&climber);
    void restart();

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    EditUser *eu;
    PaymentWindow *payment;

public:
    explicit MainWindow(QWidget *parent = 0);
    static int const EXIT_CODE_REBOOT = -1;
    ~MainWindow();
};
