#include "payment.h"
#include "ui_payment.h"

Payment::Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    expirationDate = ui->calendarWidget->selectedDate();
    ui->calendarWidget->setMinimumDate(expirationDate);

    connect(parent, SIGNAL(updateClimberInfo(Climber *)),
            this, SLOT(updateClimberInfo(Climber *)));

}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_comboBox_currentIndexChanged(int index)
{
    ui->calendarWidget->setSelectedDate(expirationDate.addMonths(index+1));
}

void Payment::updateClimberInfo(Climber *climber)
{
    qDebug() << "Name: " << climber->getName() << endl << "EXP: " << climber->getExpirationDate() << endl;
    name = climber->getName();
    expirationDate = climber->getExpirationDate();
    ui->calendarWidget->setSelectedDate(expirationDate);
}
