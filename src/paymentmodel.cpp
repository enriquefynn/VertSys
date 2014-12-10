#include <QSqlRecord>
#include <QSqlTableModel>
#include "paymentmodel.h"

PaymentModel::PaymentModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setEditStrategy(QSqlTableModel::OnRowChange);
}

bool PaymentModel::insertPayment(Payment &payment)
{
    QSqlRecord rec = record();
    rec.setValue("email", payment.getEmail());
    rec.setValue("paymentDate", payment.getPaymentDate());
    rec.setValue("expirationDate", payment.getExpirationDate());
    rec.setValue("value", payment.getValue());
    bool ret = insertRecord(-1, rec);
    submitAll();
    return ret;
}
