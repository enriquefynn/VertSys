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

    connect(this, SIGNAL(toggleActivity()),
        ui->tabWidget, SLOT(toggleActivity()));

    connect(this, SIGNAL(updateClimberInfo()),
        ui->tabWidget, SLOT(updateClimberInfo()));
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
}

void MainWindow::insertClimber(Climber *&climber)
{
    emit insertClimberInDB(climber);
}

void MainWindow::on_actionRemove_Climber_triggered()
{
    emit removeClimber();
}

void MainWindow::rowSelected(QModelIndex x, QModelIndex y)
{
    Q_UNUSED(y);
    if (x.isValid())
        ui->actionRemove_Climber->setEnabled(true);
    else
        ui->actionRemove_Climber->setEnabled(false);
}

void MainWindow::on_actionToggleActivity_Climber_triggered()
{
    emit toggleActivity();
}

void MainWindow::on_actionPay_Climber_triggered()
{
    payment = new Payment(this);
    emit updateClimberInfo();
    payment->show();
}

void MainWindow::recvClimberInfo(Climber *climber)
{
    qDebug() << climber->getName();
    emit updateClimberInfo(climber);
}
