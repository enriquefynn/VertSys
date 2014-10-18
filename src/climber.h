#pragma once
#include <QDate>

class Climber
{
private:
    QString name, phone, address, email, status;
    QDate expirationDate, startDate;

public:
    Climber();
    Climber(QString &name, QString &phone, QString &address, QString &email, QDate &expirationDate, QDate &startDate, QString &status);
    inline QString getName() {return name;}
    inline QString getPhone() {return phone;}
    inline QString getAddress() {return address;}
    inline QString getEmail() {return email;}
    inline QDate getExpirationDate() {return expirationDate;}
    inline QDate getStartDate() {return startDate;}
    inline QString getStatus() {return status;}
};
