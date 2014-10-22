#pragma once

#include <QValidator>
#include <QDebug>

class EmailValidator : public QValidator
{
    Q_OBJECT
public:
    explicit EmailValidator(QObject *parent = 0);
    QValidator::State validate(QString &input, int &pos) const;
    static bool isValid(QString str);
};
