#pragma once

#include <QStyledItemDelegate>
#include <QDate>

class DateFormatDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DateFormatDelegate(QObject *parent = 0, QString format = "dd/MM/yyyy");
    QString displayText(const QVariant &value, const QLocale &locale) const;

private:
    QString dateFormat;
};
