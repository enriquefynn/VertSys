#include "registeruser.h"
#include "ui_registeruser.h"
#include "mainwindow.h"
#include <QMessageBox>

RegisterUser::RegisterUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterUser)
{
    ui->setupUi(this);
}

RegisterUser::~RegisterUser()
{
    delete ui;
}

void RegisterUser::on_buttonBox_accepted()
{
    MainWindow conn;
    conn.connOpen();

    QString name, phone, address;
    name = ui->lineEdit_name->text();
    phone = ui->lineEdit_phone->text();
    address = ui->lineEdit_address->text();

    QSqlQuery query;
    query.prepare("insert into contacts (name, phone, address) values ('"+name+"','"+phone+"','"+address+"')");
    if(query.exec()){
        QMessageBox::critical(this,tr("Save"),tr("Saved"));
    }
    conn.connClose();
}
