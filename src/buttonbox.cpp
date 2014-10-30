#include <QSignalMapper>

#include "buttonbox.h"

ButtonBox::ButtonBox(int edit, QWidget *parent) :
    QDialogButtonBox(parent)
{
    signalMapper = new QSignalMapper(this);

    connect(this, SIGNAL(accepted()), signalMapper, SLOT(map()));

    signalMapper->setMapping(this, edit);

    connect(signalMapper, SIGNAL(mapped(int)),
        this, SIGNAL(accepted(int)));

    /*
        buttonBox = new ButtonBox(RegisterUser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);
*/
}
