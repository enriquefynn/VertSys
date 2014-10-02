#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registeruser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("contacts");
    model->select();

    qDebug() << model->lastError().text();

    ui->tableView_listUsers->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_Climber_triggered()
{
    ru = new RegisterUser(this);
    ru->show();
}
