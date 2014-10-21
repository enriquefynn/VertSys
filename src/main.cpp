#include <QApplication>
#include <QTableView>
#include <QMessageBox>

#include "mainwindow.h"
#include "model.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/general/icons/New-climber.png"));
    DBManager db;
    if (!db.openDB())
        QMessageBox::critical(0, "Base de dados", "Não foi possível conectar ao banco de dados\n"
                              "Entre em contato com o desenvolvedor", QMessageBox::Cancel);

    MainWindow w;
    w.show();

    return a.exec();
}
