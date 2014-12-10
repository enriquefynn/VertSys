#include <QtDebug>
#include "reportwindow.h"
#include "ui_report.h"

#include <QSqlQuery>
#include <QSqlRelation>

ReportWindow::ReportWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);

    ui->StartDateEdit->setDate(QDate::currentDate());
    ui->EndDateEdit->setDate(ui->StartDateEdit->date().addMonths(1));

    paymentModel = new PaymentModel(this);
    paymentModel->setTable("payment");
    paymentModel->setRelation(paymentModel->fieldIndex("email"), QSqlRelation("climber", "email", "name"));
    paymentModel->select();
    paymentModel->setHeaderData(PaymentFields::email, Qt::Horizontal, QObject::tr("Nome"));
    paymentModel->setHeaderData(PaymentFields::paymentDate, Qt::Horizontal, QObject::tr("Pago em"));
    paymentModel->setHeaderData(PaymentFields::expirationDate, Qt::Horizontal, QObject::tr("Expira em"));
    paymentModel->setHeaderData(PaymentFields::value, Qt::Horizontal, QObject::tr("Valor"));

    proxyPaymentModel = new DateSortFilterProxyModel(this);
    proxyPaymentModel->setSourceModel(paymentModel);
    proxyPaymentModel->setDynamicSortFilter(true);

    ui->tableViewFilteredContent->setModel(proxyPaymentModel);
    ui->tableViewFilteredContent->setColumnHidden(0,true);
    ui->tableViewFilteredContent->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewFilteredContent->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewFilteredContent->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewFilteredContent->setAlternatingRowColors(true);
    ui->tableViewFilteredContent->setSortingEnabled(true);
    ui->tableViewFilteredContent->sortByColumn(PaymentFields::paymentDate, Qt::AscendingOrder);

    connect(this, SIGNAL(dateChanged(QDate)),
            this, SLOT(dateFilterChanged()));
}

ReportWindow::~ReportWindow()
{
    delete ui;
}

void ReportWindow::on_buttonBox_rejected()
{
    this->close();
}

void ReportWindow::on_buttonBox_accepted()
{

}

double ReportWindow::sumPayments()
{
    double sum = 0;
    for(int i = 0; i < proxyPaymentModel->rowCount(); ++i)
    {
        QModelIndex idx = proxyPaymentModel->index(i, PaymentFields::value);
        sum += proxyPaymentModel->data(idx).toDouble();
    }
    return sum;
}

void ReportWindow::dateFilterChanged()
{
    proxyPaymentModel->setFilterMinimumDate(ui->StartDateEdit->date());
    proxyPaymentModel->setFilterMaximumDate(ui->EndDateEdit->date());
    ui->TotalValue->setNum(sumPayments());
}

void ReportWindow::on_StartDateEdit_dateChanged(const QDate &date)
{
    emit dateChanged(date);
}

void ReportWindow::on_EndDateEdit_dateChanged(const QDate &date)
{
    emit dateChanged(date);
}
