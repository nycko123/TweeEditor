
#include <QtWidgets>

#include "FindDialog.h"

TweeFindDialog::TweeFindDialog(QPlainTextEdit *textEdit, QWidget *parent) : QDialog(parent) {
    // sets up
    currentTextEdit = new QPlainTextEdit;
    cancel = new QPushButton(tr("Cancel"));
    ok = new QPushButton(tr("Find"));

    findText = new QLineEdit;
    findText->setClearButtonEnabled(true);

    findWholeWord = new QRadioButton(tr("&Find the whole word"));
    findForward = new QRadioButton(tr("&Default option"));
    findBackward = new QRadioButton(tr("&Find backward from your cursor position"));

    findRegularExpression = new QRadioButton(tr("&Regular expression finding"));
    findIncaseSensitively = new QRadioButton(tr("&Find word incasesensitively"));
    findCaseSensitively = new QRadioButton(tr("&Find word casesensitively"));

    // basic find options
    auto *findOption = new QGroupBox(tr("Find options"));
    auto *optionLayout = new QHBoxLayout;
    optionLayout->addWidget(findWholeWord);
    optionLayout->addWidget(findForward);
    optionLayout->addWidget(findBackward);
    findOption->setLayout(optionLayout);

    // expanded finding options
    auto *findGroup = new QGroupBox(tr("Expanded finding options"));
    auto *findGroupLayout = new QVBoxLayout;
    findGroupLayout->addWidget(findIncaseSensitively);
    findGroupLayout->addWidget(findCaseSensitively);
    findGroup->setLayout(findGroupLayout);

    auto *spec = new QGroupBox(tr("Special finding option"));
    auto *specLayout = new QHBoxLayout;
    specLayout->addWidget(findRegularExpression);
    spec->setLayout(specLayout);

    findForward->setChecked(true);
    findIncaseSensitively->setChecked(true);

    currentTextEdit = textEdit;

    findText->setPlaceholderText(tr("Find the word"));

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(ok);
    buttonLayout->addWidget(cancel);

    connect(findIncaseSensitively, SIGNAL(clicked()), this, SLOT(findIncase()));
    connect(findWholeWord, SIGNAL(clicked()), this, SLOT(findWhole()));
    connect(findForward, SIGNAL(clicked()), this, SLOT(findIncase()));
    connect(findBackward, SIGNAL(clicked()), this, SLOT(findBack()));
    connect(findCaseSensitively, SIGNAL(clicked()), this, SLOT(findCase()));

    connect(findRegularExpression, SIGNAL(clicked()), this, SLOT(setRegular()));

    connect(ok, SIGNAL(clicked()), this, SLOT(findEnteredText()));
    connect(cancel, &QPushButton::clicked, this, &QDialog::close);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(findText);
    mainLayout->addWidget(findOption);
    mainLayout->addWidget(findGroup);
    mainLayout->addWidget(spec);
    mainLayout->addLayout(buttonLayout);
    this->setLayout(mainLayout);

    this->setWindowIcon(QIcon(this->windowIcon()));
    this->setWindowTitle(tr("Find"));
    this->setFont(parent->font());
    this->setFixedSize(sizeHint());
}

void TweeFindDialog::findEnteredText() {
    bool res;

    // common finding
    if (!bFindRegular)
        res = currentTextEdit->find(findText->text(), findWay);

    // regular finding
    else
        res = currentTextEdit->find(QRegularExpression(findText->text()), findWay);

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

void TweeFindDialog::setRegular() {
    bFindRegular = !bFindRegular;

    if(bFindRegular)
        findText->setPlaceholderText(tr("Find the regular expression"));
    else
        findText->setPlaceholderText(tr("Find the word"));
}