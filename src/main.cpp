#include <QApplication>
#include <QTableView>
#include <QMessageBox>

#include "mainwindow.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do
    {
        QApplication a(argc, argv);
        a.setWindowIcon(QIcon(":/general/icons/New-climber.png"));
        DBManager db;
        if (!db.openDB())
            QMessageBox::critical(0, "Base de dados", "Não foi possível conectar ao banco de dados\n"
                                  "Entre em contato com o desenvolvedor", QMessageBox::Cancel);
        MainWindow w;
        w.show();
        currentExitCode = a.exec();
    }while(currentExitCode == MainWindow::EXIT_CODE_REBOOT);

    return currentExitCode;
}
