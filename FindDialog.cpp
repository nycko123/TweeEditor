
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QRadioButton>

#include "FindDialog.h"

TweeFindDialog::TweeFindDialog(QPlainTextEdit *textEdit, QWidget *parent) : QDialog(parent) {
    // sets up
    currentTextEdit = new QPlainTextEdit;
    cancel = new QPushButton(tr("Cancel"));
    ok = new QPushButton(tr("Find"));
    findText = new QLineEdit;
    findWholeWord = new QRadioButton(tr("&Find the whole word"));
    findForward = new QRadioButton(tr("&Default option"));
    findBackward = new QRadioButton(tr("&Find backward from your cursor position"));
    findIncaseSensitively = new QRadioButton(tr("&Find word incasesensitively"));
    findCaseSensitively = new QRadioButton(tr("&Find word casesensitively"));

    // basic find options
    QGroupBox *findOption = new QGroupBox(tr("Find options"));
    QHBoxLayout *optionLayout = new QHBoxLayout;
    optionLayout->addWidget(findWholeWord);
    optionLayout->addWidget(findForward);
    optionLayout->addWidget(findBackward);
    findOption->setLayout(optionLayout);

    // expanded finding options
    QGroupBox *findWay = new QGroupBox(tr("Expanded finding options"));
    QVBoxLayout *findWayLayout = new QVBoxLayout;
    findWayLayout->addWidget(findIncaseSensitively);
    findWayLayout->addWidget(findCaseSensitively);
    findWay->setLayout(findWayLayout);

    findForward->setChecked(true);
    findIncaseSensitively->setChecked(true);

    currentTextEdit = textEdit;

    findText->setPlaceholderText(tr("Find the word"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(ok);
    buttonLayout->addWidget(cancel);

    connect(findIncaseSensitively, SIGNAL(clicked()), this, SLOT(findIncase()));
    connect(findWholeWord, SIGNAL(clicked()), this, SLOT(findWhole()));
    connect(findForward, SIGNAL(clicked()), this, SLOT(findIncase()));
    connect(findBackward, SIGNAL(clicked()), this, SLOT(findBack()));
    connect(findCaseSensitively, SIGNAL(clicked()), this, SLOT(findCase()));

    connect(ok, SIGNAL(clicked()), this, SLOT(findEnteredText()));
    connect(cancel, &QPushButton::clicked, this, &QDialog::close);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(findText);
    mainLayout->addWidget(findOption);
    mainLayout->addWidget(findWay);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);

    this->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    this->setWindowTitle(tr("Find"));
    this->setFont(parent->font());
    this->setFixedSize(sizeHint());
}

void TweeFindDialog::findEnteredText() {
    bool res = currentTextEdit->find(findText->text(), findWay);

    if (!res)
        QMessageBox::critical(this->window(), tr("Error"),
                              tr("There\'s no string named <b>%1</b>").arg(findText->text()),
                              QMessageBox::Ok);
}

// slots

void TweeFindDialog::findIncase() {
    findWay = FIND_INCASESENTIVILY;
}

void TweeFindDialog::findWhole() {
    findWay = FIND_WHOLEWORD;
}

void TweeFindDialog::findBack() {
    findWay = findWay | FIND_BACKWARD;
}

void TweeFindDialog::findCase() {
    findWay = findWay | FIND_CASESENTIVILY;
}
