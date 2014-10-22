#pragma once

#include <QSqlTableModel>
#include <QDate>
#include "payment.h"

class PaymentModel : public QSqlTableModel
{
public:
    PaymentModel(QObject *parent);
    bool insertPayment(Payment &payment);
};
