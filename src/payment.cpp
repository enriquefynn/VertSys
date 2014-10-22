#include "payment.h"

Payment::Payment(QString email, QDate paymentDate, QDate expirationDate, double value)
{
    this->email = email;
    this->paymentDate = paymentDate;
    this->expirationDate = expirationDate;
    this->value = value;
}
