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

    connect(this, SIGNAL(removeClimber()),
        ui->tabWidget, SLOT(removeClimber()));
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

void MainWindow::on_actionRemove_Climber_triggered()
{
    emit removeClimber();
}
