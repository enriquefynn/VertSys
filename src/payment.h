#pragma once

#include <QDate>

namespace PaymentFields
{
    const int email = 1;
    const int paymentDate = 2;
    const int expirationDate = 3;
    const int value = 4;
}


class Payment
{
    QString email;
    QDate paymentDate;
    QDate expirationDate;
    double value;

public:
    Payment(QString email, QDate paymentDate, QDate expirationDate, double value);
    inline QString getEmail() {return email;}
    inline QDate getPaymentDate() {return paymentDate;}
    inline QDate getExpirationDate() { return expirationDate;}
    inline double getValue() {return value;}

};
