#include "phonevalidator.h"

PhoneValidator::PhoneValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State PhoneValidator::validate(QString &input, int &pos) const
{
    //DDD
    QRegExp ddd("(\\d{2})+");
    if (ddd.exactMatch(input))
    {
        input.insert(input.length(), ") ");
        input.insert(0, "(");
        pos = input.length();
    }

    //Slash
    QRegExp slash("\\(\\d{2}\\)\\s{0,1}\\d{5}");
    if (slash.exactMatch(input))
    {
        input.insert(input.length()-1, "-");
        pos = input.length();
    }

    //Separator
    QRegExp sep("[\\(]{0,1}[\\d]\{0,2}[\\)]{0,1}\\s{0,1}\\d*-{0,1}\\d*");

    if (sep.exactMatch(input))
        return QValidator::Acceptable;

    return QValidator::Invalid;
}

bool PhoneValidator::isValid(QString str)
{
    QRegExp sep("[\\(]{0,1}[\\d]\{0,2}[\\)]{0,1}\\s*\\d*[\\-]{0,1}\\d*");
    return sep.exactMatch(str);
}
