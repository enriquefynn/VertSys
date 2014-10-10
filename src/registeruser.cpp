#include "registeruser.h"
#include "ui_registeruser.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDate>

RegisterUser::RegisterUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterUser)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_Start->setDate(QDate::currentDate());
}

RegisterUser::~RegisterUser()
{
    delete ui;
}

void RegisterUser::on_buttonBox_accepted()
{
    MainWindow conn;

    QString name, phone, address, email;
    QDate expirationDate, startDate;
    name = ui->lineEdit_Name->text();
    phone = ui->lineEdit_Phone->text();
    address = ui->lineEdit_Addr->text();
    email = ui->lineEdit_Email->text();
    expirationDate = ui->dateEdit->date();
    startDate = ui->dateEdit_Start->date();
    conn.getModel()->insertClimber(name, phone, address, email, expirationDate, startDate);
}
