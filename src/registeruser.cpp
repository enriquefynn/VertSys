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

    phoneValidator = new PhoneValidator();
    ui->lineEdit_Phone->setValidator(phoneValidator);

    emailRE = new QRegExp("^\\w+@\\w+[.\\w+]+$");
    emailVal = new QRegExpValidator(*emailRE);
    ui->lineEdit_Email->setValidator(emailVal);

    connect(this, SIGNAL(insertClimber(Climber*&)),
            static_cast<QMainWindow*>(parent), SLOT(insertClimber(Climber*&)), Qt::UniqueConnection);
}

RegisterUser::~RegisterUser()
{
    delete emailRE;
    delete emailVal;
    delete phoneValidator;
    delete ui;
}

void RegisterUser::on_buttonBox_rejected()
{
    delete this;
}

void RegisterUser::accept()
{
    QString name, phone, address, email, status;
    QDate expirationDate, startDate;
    email = ui->lineEdit_Email->text();
    //Validate Email
    if (!emailRE->exactMatch(email))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Email invalido!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        //Validate Phone
        phone = ui->lineEdit_Phone->text();
        if (!PhoneValidator::isValid(phone))
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("Telefone invalido!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        else
        {
            name = ui->lineEdit_Name->text();

            address = ui->lineEdit_Addr->text();
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
    }
}
