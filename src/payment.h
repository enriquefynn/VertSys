#ifndef PAYMENT_H
#define PAYMENT_H
#include <QDate>

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

#endif // PAYMENT_H
