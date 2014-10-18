#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(updateFilter(QString)),
        ui->tabWidget, SLOT(updateFilter(QString)));

    connect(this, SIGNAL(insertClimberInDB(Climber *&)),
        ui->tabWidget, SLOT(insertClimberInDB(Climber *&)));

    /*model = new MyModel(this);
    model->setTable("climber");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nome"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telefone"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Vencimento"));

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);

    tableView = ui->tableView_listUsers;

    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(4, Qt::AscendingOrder);
    //Date_Start
    tableView->hideColumn(5);
    //Status
    tableView->hideColumn(6);
    //Address
    tableView->hideColumn(2);
    tableView->verticalHeader()->setVisible(false);

    qDebug() << model->lastError().text();*/
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
    emit updateFilter(str);
    //TabWidget::proxyModel->setFilterRegExp(str);
}

void MainWindow::insertClimber(Climber *&climber)
{
    emit insertClimberInDB(climber);
}


