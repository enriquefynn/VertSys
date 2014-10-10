#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registeruser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new MyModel(this);
    model->setTable("climber");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableView = ui->tableView_listUsers;

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);


    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(4, Qt::AscendingOrder);
    //Status
    tableView->hideColumn(5);
    //Address
    tableView->hideColumn(2);
    tableView->verticalHeader()->setVisible(false);
    qDebug() << model->lastError().text();
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

void MainWindow::on_lineEdit_search_textChanged(const QString &str)
{
    proxyModel->setFilterRegExp(str);
}
