#include "paymentwindow.h"
#include "ui_payment.h"

PaymentWindow::PaymentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    expirationDate = ui->calendarWidget->selectedDate();
    ui->calendarWidget->setMinimumDate(expirationDate);
}

PaymentWindow::~PaymentWindow()
{
    delete ui;
}

void PaymentWindow::updateClimberInfo(Climber *&climber)
{
    name = climber->getName();
    expirationDate = climber->getExpirationDate();
    ui->calendarWidget->setSelectedDate(expirationDate);
    ui->calendarWidget->setMaximumDate(expirationDate.addYears(1));
}

void PaymentWindow::on_buttonBox_accepted()
{
    //emit setExpirationDate(ui->calendarWidget->selectedDate());
    emit setPayment(ui->calendarWidget->selectedDate(), ui->valueSpin->value());
    delete this;
}

void PaymentWindow::on_buttonBox_rejected()
{
    delete this;
}
void PaymentWindow::on_sliderPayment_sliderMoved(int position)
{
    ui->calendarWidget->setSelectedDate(expirationDate.addMonths(position));
}
