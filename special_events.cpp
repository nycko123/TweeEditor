#include <QEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QStatusBar>
#include <QPrintDialog>
#include <QPrinter>

#include "mainwindow.h"

void MainWindow::saveAsSelectedDocument(int index)
{
    qDebug() << "SaveAs called\n";
    qDebug() << "The path of the index file you want to save: " << document[index].textPath << "\n";
    qDebug() << "Is first create? " << document[index].bFirstCreate << "\n";
    qDebug() << "saveDocument called, index: " << index << "\n";

    // gets the text of the index file
    const QString text = document[index].textEdit->toPlainText();
    qDebug() << "The text of the index file: " << text << "\n";

    // gets the path of the saving file
    const QString path = QFileDialog::getSaveFileName(this, tr("Save this text"), "", tr("All files (*.*)"));
    if (path.isEmpty())
        return;

    // writes the text
    QFile file(path);
retry:
    if (!file.open(QIODevice::WriteOnly))
    {
        int res = QMessageBox::critical(this, tr("Error!"), tr("Can\'t save this file."), QMessageBox::Retry, QMessageBox::Ok);
        if (res == QMessageBox::Retry)
            goto retry;
        return;
    }
    file.write(text.toUtf8());

    file.close();

    statuBar->showMessage(tr("Save file successfully"), 3000);
}

void MainWindow::saveSelectedDocument(int index)
{
    qDebug() << "The path of the index file you want to save: " << document[index].textPath << "\n";
    qDebug() << "Is first create? " << document[index].bFirstCreate << "\n";
    qDebug() << "saveDocument called, index: " << index << "\n";

    // gets the text of the index file
    const QString text = document[currentText].textEdit->toPlainText();
    qDebug() << "The text of the index file: " << text << "\n";

    // checks if the user is the first time to create this document
    if (document[index].bFirstCreate)
    {
        qDebug() << "The file needs SaveAs\n";
        saveAsSelectedDocument(index);
        return;
    }

    // gets the path of the saving file
    const QString path = document[index].textPath;
    if (path.isEmpty())
        return;

    // writes the text
    QFile file(path);
retry:
    if (!file.open(QIODevice::WriteOnly))
    {
        int res = QMessageBox::critical(this, tr("Error!"), tr("Can\'t save this file."), QMessageBox::Retry, QMessageBox::Ok);
        if (res == QMessageBox::Retry)
            goto retry;
        return;
    }
    file.write(text.toUtf8());

    file.close();

    statuBar->showMessage(tr("Save file successfully"), 3000);
}

void MainWindow::closeSelectedDocument(int index)
{
    qDebug() << "indexText: " << currentText << "\n";

    if (document[index].textEdit->document()->isModified())
    {
        int res = QMessageBox::information(this, "TweeEdit Tip",
                                           tr("There\'re <b>some files unsaved</b>.\nDo you want save it ?"),
                                           QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes)
            saveSelectedDocument(index);
    }

    totalText--;
    tabWidget->removeTab(index);
    document.removeAt(index);

    if (totalText == 0)
    {
        save->setEnabled(false);
        saveAs->setEnabled(false);
        closeTab->setEnabled(false);
        printPage->setEnabled(false);

        addTime->setEnabled(false);
        addFileName->setEnabled(false);
        findText->setEnabled(false);
    }

    statuBar->showMessage(tr("You have just closed a text document!"), 3000);
}

void MainWindow::printCurrentDocument()
{
    if (document[currentText].textEdit->document()->isModified())
        saveDocument();

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    QPrintDialog *printDialog = new QPrintDialog(printer, this);
    printDialog->setWindowTitle("Select a printer");
    printDialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (printDialog->exec() == QDialog::Accepted)
    {
        printer = printDialog->printer();
        printer->setOutputFileName(document[currentText].textPath);
        document[currentText].textEdit->document()->print(printer);
    }
    delete printer;
    delete printDialog;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool bAccept = true;
    for (auto &i : document)
    {
        // Search for each file unsaved
        if (i.textEdit->document()->isModified())
        {
            auto res = QMessageBox::information(this, "TweeEdit Tip",
                                                tr("There\'re <b>some files unsaved</b>.\nDo you want to save them ?"),
                                                QMessageBox::Yes | QMessageBox::No);
            if (res == QMessageBox::No)
                event->accept();
            else
            {
                event->ignore();
                bAccept = false;
            }
            break;
        }
    }
    if (bAccept)
    {
        writeSettingsFromSystem();
        event->accept();
    }
}
