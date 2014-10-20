#pragma once

#include <QValidator>
#include <QDebug>

class PhoneValidator : public QValidator
{
    Q_OBJECT
public:
    explicit PhoneValidator(QObject *parent = 0);
    QValidator::State validate(QString &input, int &pos) const;
    static bool isValid(QString str);

signals:
    
public slots:

};
