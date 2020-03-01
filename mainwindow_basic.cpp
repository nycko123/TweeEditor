#include <QtWidgets>
#include <QDebug>
#include <QAction>

#include "mainwindow.h"

// basic
void MainWindow::getCurrentPage()
{
    currentText = tabWidget->currentIndex();
    qDebug() << "currentText: " << currentText << "\n";
}

void MainWindow::setEnableActions(bool isEnabled)
{
    save->setEnabled(isEnabled);
    saveAs->setEnabled(isEnabled);
    closeTab->setEnabled(isEnabled);
    printPage->setEnabled(isEnabled);

    addTime->setEnabled(isEnabled);
    addFileName->setEnabled(isEnabled);
    findText->setEnabled(isEnabled);
}

void MainWindow::languageDisplayed(const QString &str)
{
    this->selectedLanguage=str;
}
