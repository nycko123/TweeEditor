#include <QtWidgets>

#include "TweeLanguageDialog.h"

TweeLanguageDialog::TweeLanguageDialog(const QString &currentLanguage, QWidget *parent) : QDialog(parent) {
    auto *label = new QLabel(tr("Select the language displayed"));
    languageBox = new QComboBox;
    auto *addTranslation = new QLabel;
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    label->setBuddy(languageBox);

    addTranslation->setText(
            tr("No translation found? <a href=\"https://github.com/TweeChalice/TweeEditor/issues\">Add translation or report</a>")
            );
    addTranslation->setOpenExternalLinks(true);

    languageBox->addItem(EN_US);
    languageBox->addItem(ZH_CN);
    languageBox->addItem(PL_PL);

    languageBox->setCurrentText(currentLanguage);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(languageBox);
    mainLayout->addWidget(addTranslation);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
    this->setFont(parent->font());
    this->setFixedSize(sizeHint());

    connect(languageBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(updateSelection()));

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    this->setWindowTitle(tr("Language"));
}

void TweeLanguageDialog::updateSelection() {
    selectLanguage = languageBox->currentText();
}

QString TweeLanguageDialog::selectedLanguage() const {
    return this->selectLanguage;
}
