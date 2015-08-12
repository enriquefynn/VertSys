#include "dateformatdelegate.h"

DateFormatDelegate::DateFormatDelegate(QObject *parent, QString format) :
    QStyledItemDelegate(parent),
    dateFormat(format)
{
}

QString DateFormatDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    return value.toDate().toString(dateFormat);
}
