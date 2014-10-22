#pragma once

#include <QDialog>
#include <QDate>
#include <QRegExpValidator>

#include "climber.h"
#include "phonevalidator.h"
#include "emailvalidator.h"

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
    void on_buttonBox_rejected();

signals:
    void insertClimber(Climber *&climber);

private:
    Ui::RegisterUser *ui;
    const PhoneValidator *phoneValidator;
    const EmailValidator *emailValidator;

protected:
    void accept();
};
