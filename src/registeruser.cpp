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
}

RegisterUser::~RegisterUser()
{
    delete ui;
}

void RegisterUser::on_buttonBox_accepted()
{
    MainWindow conn;

    QString name, phone, address, email;
    QDate expirationDate;
    name = ui->lineEdit_Name->text();
    phone = ui->lineEdit_Phone->text();
    address = ui->lineEdit_Addr->text();
    email = ui->lineEdit_Email->text();
    expirationDate = ui->dateEdit->date();

    QSqlRecord record = conn.getModel()->record();
    record.setValue("name", name);
    record.setValue("phone", phone);
    record.setValue("address", address);
    record.setValue("email", email);
    record.setValue("expirationDate", expirationDate);
    record.setValue("status", "O");

    conn.getModel()->insertRecord(-1, record);
}
