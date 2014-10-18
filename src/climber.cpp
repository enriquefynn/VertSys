#include "climber.h"

Climber::Climber()
{
}

Climber::Climber(QString &name, QString &phone, QString &address, QString &email, QDate &expirationDate, QDate &startDate, QString &status)
{
    this->name = name;
    this->phone = phone;
    this->address = address;
    this->email = email;
    this->expirationDate = expirationDate;
    this->startDate = startDate;
    this->status = status;
}
