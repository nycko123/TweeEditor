#include <QtWidgets>

#include "mainwindow.h"

void MainWindow::addTimetoEdit() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    document[currentText].textEdit->insertPlainText(currentDateTime.toString());
}

void MainWindow::addFileNametoEdit() {
    document[currentText].textEdit->insertPlainText(tabWidget->tabText(currentText));
}

void MainWindow::fontSelect() {
    auto *fontDialog = new QFontDialog(textFont, this);
    fontDialog->setFont(QFont("Microsoft YaHei"));
    fontDialog->setWindowIcon(this->windowIcon());
    fontDialog->setWindowTitle(tr("Select the font"));
    fontDialog->setCurrentFont(this->textFont);

    if (fontDialog->exec() == QDialog::Accepted) {
        textFont = fontDialog->selectedFont();

        // updates all the font displayed
        for (auto &i : document) {
            i.textEdit->setFont(textFont);
            i.textEdit->update();
        }
    }
}

void MainWindow::findTextDialog() {
    if(!findDialog)
        findDialog = new TweeFindDialog(document[currentText].textEdit, this);

    findDialog->show();
    findDialog->raise();
}

void MainWindow::selectLanguage() {
    languageDialog = new TweeLanguageDialog(selectedLanguage, this);

    if (languageDialog->exec() == QDialog::Accepted) {
        QString language = languageDialog->selectedLanguage();

        qDebug() << "Selected language: " << language << "\n";

        selectedLanguage = language;

        QMessageBox::information(this, tr("Attention"),
                                 tr("Your language will be changed after restarting TweeEditor"),
                                 QMessageBox::Ok);
    }
}
