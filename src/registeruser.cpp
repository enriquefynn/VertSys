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

    QString name, phone, address, email, expirationDate;
    name = ui->lineEdit_Name->text();
    phone = ui->lineEdit_Phone->text();
    address = ui->lineEdit_Addr->text();
    email = ui->lineEdit_Email->text();
    expirationDate = ui->dateEdit->text();

    QSqlQuery query;
    query.prepare("insert into contacts (name, phone, address, email, expirationDate, status) values ('"+name+"','"+phone+"','"+address+"','"+email+"', '"+expirationDate+"', 'O')");
    if(query.exec()){
        QMessageBox::critical(this,tr("Save"),tr("Saved"));
    }
}
