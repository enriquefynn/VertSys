#include "emailvalidator.h"

EmailValidator::EmailValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State EmailValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos);
    input = input.toLower();
    QRegExp mailre("^\\S+$");
    if (mailre.exactMatch(input))
        return QValidator::Acceptable;
    return QValidator::Invalid;
}

bool EmailValidator::isValid(QString str)
{
    QRegExp sep("^\\S+@\\w+[.\\S+]+$");
    return sep.exactMatch(str);
}
