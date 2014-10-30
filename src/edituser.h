#pragma once

#include <QDialog>
#include <QDate>
#include <QRegExpValidator>

#include "climber.h"
#include "phonevalidator.h"
#include "emailvalidator.h"

namespace Ui {
class EditUser;
}


class EditUser : public QDialog
{
    Q_OBJECT
public:
    explicit EditUser(int row, Climber *&climber, QWidget *parent = 0);
    ~EditUser();
signals:
    void editClimber(int, Climber*&);

public slots:

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::EditUser *ui;
    const PhoneValidator *phoneValidator;
    const EmailValidator *emailValidator;
    int rowEdited;
};
