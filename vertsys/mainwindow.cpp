#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registeruser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connOpen();

    model = new QSqlTableModel(this);
    model->setTable("contacts");
    model->select();

    qDebug() << model->lastError().text();

    ui->tableView_listUsers->setModel(model);
}

MainWindow::~MainWindow()
{
    connClose();
    delete ui;
}

void MainWindow::on_pushButton_newRegister_clicked()
{
    ru = new RegisterUser(this);
    ru->show();
}
