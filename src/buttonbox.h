#pragma once

#include <QSignalMapper>
#include <QDialogButtonBox>

class ButtonBox : public QDialogButtonBox
{
    Q_OBJECT
public:
    explicit ButtonBox(QWidget *parent = 0);
    explicit ButtonBox(int edit=0, QWidget *parent = 0);

signals:
    void accepted(const int);

public slots:

private:
    QSignalMapper *signalMapper;
};
