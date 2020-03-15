#include <QtWidgets>
#include "TweeBugReportDialog.h"

#define COPY_ACTION_CNT 4

TweeBugReportDialog::TweeBugReportDialog(QWidget *parent) : QDialog(parent) {
    // sets up
    board = QApplication::clipboard();

    auto *sysNameLabel = new QLabel(tr("Your system name: "));
    // i=0
    sysNameLineEdit = new QLineEdit;
    sysNameLineEdit->setReadOnly(true);

    auto *sysProductNameLabel = new QLabel(tr("Your system product name: "));
    // i=1
    sysProductNameLineEdit = new QLineEdit;
    sysProductNameLineEdit->setReadOnly(true);

    // i=2
    auto *sysProductVersionLabel = new QLabel(tr("Your version of the system product: "));
    sysProductVersionLineEdit = new QLineEdit;
    sysProductVersionLineEdit->setReadOnly(true);

    auto sysArchLabel = new QLabel(tr("Your CPU Architecture: "));
    // i=3
    sysArchLineEdit = new QLineEdit;
    sysArchLineEdit->setReadOnly(true);

    buttonBox = new QDialogButtonBox;
    copyAction = new QAction[COPY_ACTION_CNT];

    for (int i = 0; i < COPY_ACTION_CNT; i++) {
        copyAction[i].setIcon(QIcon(":/ico/copy.png"));
        copyAction[i].setToolTip(tr("Copy this information"));

        // adds copyAction to QLineEdit and sets the text in QLineEdit
        if (i == 0) {
            connect(&copyAction[i], &QAction::triggered, this, &TweeBugReportDialog::copy0);
            sysNameLineEdit->setText(QSysInfo::prettyProductName());
            sysNameLineEdit->addAction(&copyAction[i], QLineEdit::ActionPosition::TrailingPosition);
        } else if (i == 1) {
            connect(&copyAction[i], &QAction::triggered, this, &TweeBugReportDialog::copy1);
            sysProductNameLineEdit->setText(QSysInfo::productType());
            sysProductNameLineEdit->addAction(&copyAction[i], QLineEdit::ActionPosition::TrailingPosition);
        } else if (i == 2) {
            connect(&copyAction[i], &QAction::triggered, this, &TweeBugReportDialog::copy2);
            sysProductVersionLineEdit->setText(QSysInfo::productVersion());
            sysProductVersionLineEdit->addAction(&copyAction[i], QLineEdit::ActionPosition::TrailingPosition);
        } else if (i == 3) {
            connect(&copyAction[i], &QAction::triggered, this, &TweeBugReportDialog::copy3);
            sysArchLineEdit->setText(QSysInfo::currentCpuArchitecture());
            sysArchLineEdit->addAction(&copyAction[i], QLineEdit::ActionPosition::TrailingPosition);
        }
    }

    sysNameLabel->setBuddy(sysNameLineEdit);
    sysProductNameLabel->setBuddy(sysProductNameLineEdit);
    sysProductVersionLabel->setBuddy(sysProductVersionLineEdit);
    sysArchLabel->setBuddy(sysArchLineEdit);

    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    auto *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(sysNameLabel);
    mainLayout->addWidget(sysNameLineEdit);

    mainLayout->addWidget(sysProductNameLabel);
    mainLayout->addWidget(sysProductNameLineEdit);

    mainLayout->addWidget(sysProductVersionLabel);
    mainLayout->addWidget(sysProductVersionLineEdit);

    mainLayout->addWidget(sysArchLabel);
    mainLayout->addWidget(sysArchLineEdit);

    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
    this->setFont(parent->font());
    this->setWindowIcon(parent->windowIcon());
    this->setWindowTitle(tr("Bug report"));
    this->setFixedSize(sizeHint());

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void TweeBugReportDialog::copy0() {
    board->clear();
    board->setText(sysNameLineEdit->text());
}

void TweeBugReportDialog::copy1() {
    board->clear();
    board->setText(sysProductNameLineEdit->text());
}

void TweeBugReportDialog::copy2() {
    board->clear();
    board->setText(sysProductVersionLineEdit->text());
}

void TweeBugReportDialog::copy3() {
    board->clear();
    board->setText(sysArchLineEdit->text());
}