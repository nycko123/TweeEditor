#include <QtWidgets>
#include <QDebug>
#include <QTime>

#include "mainwindow.h"


void MainWindow::addTimetoEdit()
{
    QTime currentTime=QTime::currentTime();
    document[currentText].textEdit->appendPlainText(currentTime.toString());
} 

void MainWindow::addFileNametoEdit()
{
    document[currentText].textEdit->appendPlainText(tabWidget->tabText(currentText));
}

void MainWindow::fontSelect()
{
    bool bSelect;
    QFont selectedFont = QFontDialog::getFont(&bSelect, this);
    if (bSelect)
    {
        textFont = selectedFont;

        // updates all the font displayed
        for (auto &i : document)
        {
            i.textEdit->setFont(textFont);
            i.textEdit->update();
        }
    }
}

void MainWindow::findTextDialog()
{
    findDialog = new TweeFindDialog(document[currentText].textEdit, this);
    findDialog->setModal(true);
    findDialog->show();
}