#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#include "registeruser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //TODO: Create a header/code file for db operation is better
    void connClose() {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
        db = QSqlDatabase::addDatabase("QSQLITE");
        // FIXME: use realtive paths
        db.setDatabaseName("/home/rodrigo/src/fractal/vertsys/vertsys.db");

        if(!db.open()) {
            qDebug() << "Failed to open database.";
            return false;
         }
        else {
            qDebug() << "Connected.";
            bool found = false;
            foreach (QString table, db.tables()) {
                if(table == "contacts") {
                    found = true;
                    break;
                }
            }
            if(!found) {
                QSqlQuery query(db);
                query.exec("CREATE TABLE contacts (name VARCHAR(32), phone VARCHAR(16), address VARCHAR(40))");
            }
            return true;
        }
    }

private slots:
    void on_pushButton_newRegister_clicked();

private:
    Ui::MainWindow *ui;
    RegisterUser *ru;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
