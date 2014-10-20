#pragma once

#include <QDialog>
#include <QDate>
#include <QDebug>

#include "climber.h"

namespace Ui {
class Payment;
}

class Payment : public QDialog
{
    Q_OBJECT

public slots:
    void updateClimberInfo(Climber *climber);

public:
    explicit Payment(QWidget *parent = 0);
    ~Payment();
    
private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Payment *ui;
    QString name;
    QDate expirationDate;
};
