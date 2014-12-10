#include "datesortfilterproxymodel.h"
#include "payment.h"

#include <QtDebug>

DateSortFilterProxyModel::DateSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void DateSortFilterProxyModel::setFilterMinimumDate(const QDate &date)
{
    minDate = date;
    invalidateFilter();
}

void DateSortFilterProxyModel::setFilterMaximumDate(const QDate &date)
{
    maxDate = date;
    invalidateFilter();
}

bool DateSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, PaymentFields::paymentDate, sourceParent);
    return dateInRange(sourceModel()->data(index).toDate());
}

bool DateSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);
    if (leftData.type() == QVariant::Date)
        return leftData.toDate() < rightData.toDate();
    else
    {
        if(left.column() == PaymentFields::value && right.column() == PaymentFields::value)
            return leftData.toFloat() < rightData.toFloat();
        else
            return QString::localeAwareCompare(leftData.toString(), rightData.toString()) < 0;
    }
}

bool DateSortFilterProxyModel::dateInRange(const QDate &date) const
{
    return (date >= minDate && date <= maxDate);
}
