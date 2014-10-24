#include <QApplication>
#include <QTableView>
#include <QMessageBox>
#include <QTranslator>

#include "mainwindow.h"
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do
    {
        QApplication a(argc, argv);

        QTranslator qtTranslator;
        qtTranslator.load("qt_" + QLocale::system().name(),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        a.installTranslator(&qtTranslator);

        QTranslator vertSysTranslator;
        vertSysTranslator.load("vertsys_" + QLocale::system().name());
        a.installTranslator(&vertSysTranslator);

        a.setWindowIcon(QIcon(":/general/icons/New-climber.png"));
        DBManager db;
        if (!db.openDB())
            QMessageBox::critical(0, "Database", "It wasn't possible to connect to database\n\
Contact the developer!", QMessageBox::Cancel);
        MainWindow w;
        w.show();
        currentExitCode = a.exec();
    }while(currentExitCode == MainWindow::EXIT_CODE_REBOOT);

    return currentExitCode;
}
