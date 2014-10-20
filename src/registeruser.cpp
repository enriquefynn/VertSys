#include "registeruser.h"
#include "ui_registeruser.h"
#include "mainwindow.h"

RegisterUser::RegisterUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterUser)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_Start->setDate(QDate::currentDate());
    connect(this, SIGNAL(insertClimber(Climber*&)),
            static_cast<QMainWindow*>(parent), SLOT(insertClimber(Climber*&)), Qt::UniqueConnection);
}

RegisterUser::~RegisterUser()
{
    delete ui;
}

void RegisterUser::on_buttonBox_accepted()
{
    QString name, phone, address, email, status;
    QDate expirationDate, startDate;
    name = ui->lineEdit_Name->text();
    phone = ui->lineEdit_Phone->text();
    address = ui->lineEdit_Addr->text();
    email = ui->lineEdit_Email->text();
    expirationDate = ui->dateEdit->date();
    startDate = ui->dateEdit_Start->date();
    int comboIdx = ui->comboBox->currentIndex();
    if (!comboIdx)
        status = "A";
    else
        status = "D";
    Climber *c = new Climber(name, phone, address, email, expirationDate, startDate, status);
    emit insertClimber(c);
    delete this;
}

void RegisterUser::on_buttonBox_rejected()
{
    delete this;
}
