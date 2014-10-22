#pragma once

#include <QDialog>
#include <QDate>
#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

#include "climber.h"

namespace Ui {
class Payment;
}

class PaymentWindow : public QDialog
{
    Q_OBJECT

public slots:
    void updateClimberInfo(Climber *&climber);

public:
    explicit PaymentWindow(QWidget *parent = 0);
    ~PaymentWindow();
    
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_sliderPayment_sliderMoved(int position);

signals:
    void setPayment(QDate date, double value);

private:
    Ui::Payment *ui;
    QString name;
    QDate expirationDate;
};
