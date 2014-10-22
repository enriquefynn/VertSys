#ifndef PAYMENTMODEL_H
#define PAYMENTMODEL_H

#include <QSqlTableModel>
#include <QDate>
#include "payment.h"

class PaymentModel : public QSqlTableModel
{
public:
    PaymentModel(QObject *parent);
    bool insertPayment(Payment &payment);
};

#endif // PAYMENTMODEL_H
