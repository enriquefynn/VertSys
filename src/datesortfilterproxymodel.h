#pragma once

#include<QDate>
#include<QSortFilterProxyModel>

class DateSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    DateSortFilterProxyModel(QObject *parent = 0);
    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(const QDate &date);
    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(const QDate &date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    bool dateInRange(const QDate &date) const;
    QDate minDate;
    QDate maxDate;
};
