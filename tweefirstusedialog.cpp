#include <QPushButton>
#include <QTextEdit>
#include <QRadioButton>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>

#include "tweefirstusedialog.h"

void TweeFirstUseDialog::setAcStatu()
{
    ok->setEnabled(true);
}

void TweeFirstUseDialog::setDisStatu()
{
    ok->setEnabled(false);
}

TweeFirstUseDialog::TweeFirstUseDialog(QWidget *parent) : QDialog(parent)
{
    introduce = new QTextEdit;
    licenseDisplay = new QTextEdit;
    acceptLic = new QRadioButton(tr("I have read this CAREFULLY and agree with it"));
    disagreeLic = new QRadioButton(tr("I DO NOT accept this license and exit"));
    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel (Exit)"));

    bool res = readLicense();
    if (!res)
    {
        parent->close();
        exit(0);
    }

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(introduce);
    mainLayout->addWidget(licenseDisplay);

    QGroupBox *buttonGroup = new QGroupBox(tr("Read the license and select"));
    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupLayout->addWidget(acceptLic);
    groupLayout->addWidget(disagreeLic);
    buttonGroup->setLayout(groupLayout);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(ok);
    buttonLayout->addWidget(cancel);

    mainLayout->addWidget(buttonGroup);
    mainLayout->addLayout(buttonLayout);

    ok->setEnabled(false);

    this->setLayout(mainLayout);
    this->setFont(parent->font());
    this->setFixedSize(sizeHint());
    this->setModal(true);

    introduce->setReadOnly(true);
    licenseDisplay->setReadOnly(true);

    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(cancel, SIGNAL(clicked()), parent, SLOT(close()));

    connect(ok, SIGNAL(clicked()), this, SLOT(close()));

    connect(acceptLic, SIGNAL(pressed()), this, SLOT(setAcStatu()));
    connect(disagreeLic, SIGNAL(pressed()), this, SLOT(setDisStatu()));
}

bool TweeFirstUseDialog::readLicense()
{
    QFile file(":/LICENSE"), file2(":/README.md");
    if (!file.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, tr("Error"),
                              tr("Error preparing data!"), QMessageBox::Ok);
        return false;
    }
    QTextStream stream(&file), stream2(&file2);

    introduce->setMarkdown(stream2.readAll());
    licenseDisplay->setPlainText(stream.readAll());

    file.close();
    file2.close();
    return true;
}