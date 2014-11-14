#include "edituser.h"
#include "ui_edituser.h"
#include "mainwindow.h"

EditUser::EditUser(int row, Climber*& climber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);

    phoneValidator = new PhoneValidator();
    emailValidator = new EmailValidator();

    rowEdited = row;

    ui->lineEdit_Phone->setValidator(phoneValidator);
    ui->lineEdit_Email->setValidator(emailValidator);

    ui->lineEdit_Name->setText(climber->getName());
    ui->lineEdit_Phone->setText(climber->getPhone());
    ui->lineEdit_Addr->setText(climber->getAddress());
    ui->lineEdit_Email->setText(climber->getEmail());
    ui->observationsTextEdit->setPlainText(climber->getObservations());
    ui->dateEdit->setDate(climber->getExpirationDate());
    ui->dateEdit_Start->setDate(climber->getStartDate());
    QString status = climber->getStatus();
    if(status == "A")
        ui->comboBox->setCurrentIndex(0);
    else
        ui->comboBox->setCurrentIndex(1);

    connect(this, SIGNAL(editClimber(int, Climber*&)),
            static_cast<QMainWindow*>(parent), SLOT(editClimber(int, Climber*&)), Qt::UniqueConnection);
}

EditUser::~EditUser()
{
    delete phoneValidator;
    delete emailValidator;
    delete ui;
}

void EditUser::on_buttonBox_rejected()
{
    delete this;
}

//FIXME: Set modified fields only
//FIXME: Don't repeat yourself
void EditUser::on_buttonBox_accepted()
{
    QString name, phone, address, email, status, observations;
    QDate expirationDate, startDate;
    email = ui->lineEdit_Email->text();
    //Validate Email
    if (!EmailValidator::isValid(email))
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
            observations = ui->observationsTextEdit->toPlainText();

            expirationDate = ui->dateEdit->date();
            startDate = ui->dateEdit_Start->date();
            int comboIdx = ui->comboBox->currentIndex();
            if (!comboIdx)
                status = "A";
            else
                status = "D";
            Climber *c = new Climber(name, phone, address, email, expirationDate, startDate, status, observations);
            emit editClimber(rowEdited, c);
            delete this;
        }
    }
}
