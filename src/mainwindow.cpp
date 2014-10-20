#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(updateFilter(QString)),
        ui->tabWidget, SLOT(updateFilter(QString)), Qt::UniqueConnection);

    connect(this, SIGNAL(insertClimberInDB(Climber *&)),
        ui->tabWidget, SLOT(insertClimberInDB(Climber *&)), Qt::UniqueConnection);

    connect(this, SIGNAL(removeClimber()),
        ui->tabWidget, SLOT(removeClimber()), Qt::UniqueConnection);

    connect(this, SIGNAL(toggleActivity()),
        ui->tabWidget, SLOT(toggleActivity()), Qt::UniqueConnection);

    connect(this, SIGNAL(updateClimberInfo()),
        ui->tabWidget, SLOT(updateClimberInfo()), Qt::UniqueConnection);

    connect(this, SIGNAL(commitExpirationDate(QDate)),
        ui->tabWidget, SLOT(commitExpirationDate(QDate)), Qt::UniqueConnection);
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

    connect(this, SIGNAL(updateClimberInfo(Climber *&)),
            payment, SLOT(updateClimberInfo(Climber *&)), Qt::UniqueConnection);

    connect(payment, SIGNAL(setExpirationDate(QDate)),
            this, SLOT(setExpirationDate(QDate)), Qt::UniqueConnection);

    emit updateClimberInfo();
    payment->show();
}

void MainWindow::recvClimberInfo(Climber *&climber)
{
    emit updateClimberInfo(climber);
}

void MainWindow::setExpirationDate(QDate date)
{
    emit commitExpirationDate(date);
}

void MainWindow::updateActivateOption(int idx)
{
    ui->actionToggleActivity_Climber->setEnabled(true);
    if (idx == 0)
        ui->actionToggleActivity_Climber->setText("Inativar");
    else if (idx == 1)
        ui->actionToggleActivity_Climber->setEnabled(false);
    else
        ui->actionToggleActivity_Climber->setText("Ativar");
}
