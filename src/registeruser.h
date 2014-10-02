#pragma once

#include <QDialog>

namespace Ui {
class RegisterUser;
}

class RegisterUser : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterUser(QWidget *parent = 0);
    ~RegisterUser();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RegisterUser *ui;
};
