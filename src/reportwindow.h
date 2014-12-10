#pragma once

#include <QDialog>
#include <QSortFilterProxyModel>
#include "paymentmodel.h"
#include "datesortfilterproxymodel.h"

namespace Ui {
class Report;
}

class ReportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = 0);
    ~ReportWindow();

signals:
    void dateChanged(const QDate &filter);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    double sumPayments();
    void dateFilterChanged();
    void on_StartDateEdit_dateChanged(const QDate &date);
    void on_EndDateEdit_dateChanged(const QDate &date);
    void exportCSV();

private:
    Ui::Report *ui;
    PaymentModel *paymentModel;
    DateSortFilterProxyModel *proxyPaymentModel;
};

