#pragma once

#include <QSqlRelationalTableModel>
#include <QDate>
#include "payment.h"

class PaymentModel : public QSqlRelationalTableModel
{
public:
    PaymentModel(QObject *parent);
    bool insertPayment(Payment &payment);
};
