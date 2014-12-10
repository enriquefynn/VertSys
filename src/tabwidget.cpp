#include "tabwidget.h"
#include "mainwindow.h"
#include "payment.h"
#include "registeruser.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setupModel();
    setupTabs();
    connect(this, SIGNAL(currentChanged(int)),
           this, SLOT(updateIdx()), Qt::UniqueConnection);

    connect(this, SIGNAL(updateClimberInfo(Climber*&)),
            static_cast<QMainWindow*>(parent->parent()), SLOT(recvClimberInfo(Climber*&)), Qt::UniqueConnection);

    connect(currentWidget(),SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(editClimber(const QModelIndex&)), Qt::UniqueConnection);

    connect(this, SIGNAL(editClimberWindow(int, Climber*)),
            static_cast<QMainWindow*>(parent->parent()), SLOT(displayClimberInfo(int, Climber*)), Qt::UniqueConnection);

    connect(this, SIGNAL(updateActivateOption(int)),
            static_cast<QMainWindow*>(parent->parent()), SLOT(updateActivateOption(int)), Qt::UniqueConnection);
}

void TabWidget::setupModel()
{
    climberModel = new ClimberModel(this);
    climberModel->setTable("climber");
    climberModel->select();
    climberModel->setHeaderData(VertSys::name, Qt::Horizontal, QObject::tr("Nome"));
    climberModel->setHeaderData(VertSys::phone, Qt::Horizontal, QObject::tr("Telefone"));
    climberModel->setHeaderData(VertSys::email, Qt::Horizontal, QObject::tr("Email"));
    climberModel->setHeaderData(VertSys::expirationDate, Qt::Horizontal, QObject::tr("Vencimento"));

    proxyTextModel = new QSortFilterProxyModel(this);
    proxyTextModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyTextModel->setSourceModel(climberModel);

    paymentModel = new PaymentModel(this);
    paymentModel->setTable("payment");
}

void TabWidget::setupTabs()
{
    QStringList groups;
    QList<QString> charNames;
    groups << tr("Mensalistas") << tr("Todos") << tr("Diarios");
    charNames << "A" << "" << "D";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(proxyTextModel);
        proxyModel->setDynamicSortFilter(true);

        QTableView *tableView = new QTableView;

        tableView->setModel(proxyModel);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);

        tableView->hideColumn(VertSys::startDate);
        tableView->hideColumn(VertSys::status);
        tableView->hideColumn(VertSys::address);
        tableView->hideColumn(VertSys::observations);

        //Connect the select to disable buttons
        QItemSelectionModel *sm = tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                parentWidget()->parentWidget(), SLOT(rowSelected(QModelIndex,QModelIndex)), Qt::UniqueConnection);

        proxyModel->setFilterRegExp(QRegExp(charNames[i], Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(VertSys::status);
        proxyModel->sort(VertSys::expirationDate, Qt::AscendingOrder);
        addTab(tableView, str);
    }
}

void TabWidget::updateFilter(QString str)
{
    proxyTextModel->setFilterRegExp(str);
}

void TabWidget::insertClimberInDB(Climber *&climber)
{
    qDebug() << "INSERTED: " << climber->getName();
    bool ret = climberModel->insertClimber(climber);
    if(ret)
        updateIdx();
    else
        qDebug() << climberModel->lastError().text();
}

void TabWidget::removeClimber()
{
    int row = selectedRow();
    climberModel->removeClimber(row);
}

void TabWidget::editClimber(const QModelIndex& index)
{
    Q_UNUSED(index);

    int row = selectedRow();
    emit editClimberWindow(row, climberModel->getClimber(row));
}

void TabWidget::editClimberInDB(int row, Climber *&climber)
{
    qDebug() << "EDITED: " << climber->getName() << " " << row;
    climberModel->editClimber(row, climber);
}

//FIXME: Not really working
void TabWidget::updateIdx()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    emit updateActivateOption(currentIndex());
    temp->setCurrentIndex(QModelIndex());

    // Connect each tab with editClimber
    connect(currentWidget(),SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(editClimber(const QModelIndex&)), Qt::UniqueConnection);
}

void TabWidget::toggleActivity()
{
    int row = selectedRow();
    climberModel->toggleActivity(row);
}

int TabWidget::selectedRow()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    QItemSelectionModel *selectionModel = temp->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();
    QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(temp->model());
    QModelIndex idx;
    int row;
    foreach (idx, indexes)
        row = proxyTextModel->mapToSource(proxy->mapToSource(idx)).row();
    return row;
}

void TabWidget::updateClimberInfo()
{
    int row = selectedRow();
    emit updateClimberInfo(climberModel->getClimber(row));
}

void TabWidget::setPayment(QDate expirationDate, double value)
{
    int row = selectedRow();
    Climber *c = climberModel->getClimber(row);
    Payment payment(c->getEmail(), QDate::currentDate(), expirationDate, value);
    if (climberModel->updateExpirationDate(row, expirationDate) && paymentModel->insertPayment(payment))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pagamento do escalador " + c->getName() + " efetuado com sucesso!\nVencimento \
na data: " + expirationDate.toString("dd/MM/yyyy") + "\nValor: R$ " + QString::number(value));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Não foi possível efetuar o pagamento!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    delete c;
}
