#include "tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setupModel();
    setupTabs();
    connect(this, SIGNAL(currentChanged(int)),
           this, SLOT(updateIdx()), Qt::UniqueConnection);

    connect(this, SIGNAL(updateClimberInfo(Climber*&)),
            static_cast<QMainWindow*>(parent->parent()), SLOT(recvClimberInfo(Climber*&)), Qt::UniqueConnection);
}

void TabWidget::setupModel()
{
    model = new MyModel(this);
    model->setTable("climber");
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nome"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Telefone"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Vencimento"));
    proxyTextModel = new QSortFilterProxyModel(this);
    proxyTextModel->setSourceModel(model);
}

void TabWidget::setupTabs()
{
    QStringList groups;
    QList<QString> charNames;
    groups << tr("Ativos") << tr("Todos") << tr("Inativos") << tr("Diarios");
    charNames << "A" << "" << "I" << "D";

    for (int i = 0; i < groups.size(); ++i) {
        QString str = groups.at(i);

        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(proxyTextModel);
        proxyModel->setDynamicSortFilter(true);

        QTableView *tableView = new QTableView;

        tableView->setModel(proxyModel);
        tableView->setSortingEnabled(true);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        //tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->hide();
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        //Date_Start
        tableView->hideColumn(5);
        //Status
        tableView->hideColumn(6);
        //Address
        tableView->hideColumn(2);
        tableView->verticalHeader()->setVisible(false);

        //Connect the select to disable buttons
        QItemSelectionModel *sm = tableView->selectionModel();
        connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                parentWidget()->parentWidget(), SLOT(rowSelected(QModelIndex,QModelIndex)), Qt::UniqueConnection);

        proxyModel->setFilterRegExp(QRegExp(charNames[i], Qt::CaseInsensitive));
        proxyModel->setFilterKeyColumn(6);
        proxyModel->sort(4, Qt::AscendingOrder);
        addTab(tableView, str);
    }
}

void TabWidget::updateFilter(QString str)
{
    proxyTextModel->setFilterRegExp(str);
}

void TabWidget::insertClimberInDB(Climber *&climber)
{
    qDebug() << climber->getName();
    model->insertClimber(climber);
    updateIdx();
}

void TabWidget::removeClimber()
{
    int row = selectedRow();
    model->removeClimber(row);
}

//FIXME: Not really working
void TabWidget::updateIdx()
{
    QTableView *temp = static_cast<QTableView*>(currentWidget());
    qDebug() << QModelIndex() << endl;
    temp->setCurrentIndex(QModelIndex());
}

void TabWidget::toggleActivity()
{
    int row = selectedRow();
    model->toggleActivity(row);
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
        row = proxy->mapToSource(idx).row();
    return row;
}

void TabWidget::updateClimberInfo()
{
    int row = selectedRow();
    emit updateClimberInfo(model->getClimber(row));
}

void TabWidget::commitExpirationDate(QDate date)
{
    int row = selectedRow();
    Climber *c = model->getClimber(row);
    if (model->updateExpirationDate(row, date))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Pagamento do escalador " + c->getName() + " efetuado com sucesso!\nVencimento \
na data: " + date.toString("dd/MM/yyyy"));
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
