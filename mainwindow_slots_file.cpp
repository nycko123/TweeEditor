#include <QtWidgets>
#include <QPrintDialog>
#include <QPrinter>
#include <QTime>
#include <QDebug>

#include "mainwindow.h"

// common 'file' slots

void MainWindow::newDocument(const QString &text, const QString &title, const QString &textPath)
{
    bool bEmptyPath = textPath.isEmpty();

    setEnableActions(true);

    // default: put the new widget to the back of the queue
    totalText++;
    countText++;

    document.push_back(Document());

    document.back().textEdit->setPlainText(text);
    document.back().textPath = textPath;
    if (!bEmptyPath)
        document.back().bFirstCreate = false;

    document.back().textEdit->setFont(textFont);

    tabWidget->addTab(document.back().textEdit, QIcon(":/ico/document.png"),
                      (bEmptyPath ? (tr("untitled-%1").arg(countText)) : title));
    tabWidget->setTabsClosable(true);
    tabWidget->update();
    tabWidget->setCurrentWidget(document.back().textEdit);

    qDebug() << "Is first create? " << document.back().bFirstCreate << "\n";
    qDebug() << "newDocument called, currentText: " << currentText << "\n";
}

void MainWindow::openDocument()
{
    // opens text
    const QString path = QFileDialog::getOpenFileName(this, tr("Select a documnet"), "", tr("All files (*.*)"));
    qDebug() << "Opened path: " << path << "\n";
    if (path.isEmpty())
        return;

    // reads the text
    QFile file(path);
retry:
    if (!file.open(QIODevice::ReadOnly))
    {
        statuBar->showMessage(tr("Open failed!"), 3000);
        int res = QMessageBox::critical(this, tr("Error!"), tr("Can\'t open this file"), QMessageBox::Retry, QMessageBox::Ok);
        if (res == QMessageBox::Retry)
            goto retry;
        return;
    }
    QTextStream stream(&file);
    QString text = stream.readAll();

    // gets the name of the text
    QFileInfo info(path);

    // displays the text
    newDocument(text, info.fileName(), path);
}

void MainWindow::saveDocument()
{
    qDebug() << "The path of the current file you want to save: " << document[currentText].textPath << "\n";
    qDebug() << "Is first create? " << document[currentText].bFirstCreate << "\n";
    qDebug() << "saveDocument called, currentText: " << currentText << "\n";

    // gets the text of the current file
    const QString text = document[currentText].textEdit->toPlainText();
    qDebug() << "The text of the current file: " << text << "\n";

    // checks if the user is the first time to create this document
    if (document[currentText].bFirstCreate)
    {
        qDebug() << "The file needs SaveAs\n";
        saveAsDocument();
        return;
    }

    // gets the path of the saving file
    const QString path = document[currentText].textPath;
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
    QFileInfo info(file);
    tabWidget->setTabText(currentText, info.fileName());

    file.close();

    document[currentText].textEdit->document()->setModified(false);
    document[currentText].bFirstCreate = false;

    statuBar->showMessage(tr("Save file successfully"), 3000);
}

void MainWindow::closeDocument()
{
    qDebug() << "currentText: " << currentText << "\n";

    if (document[currentText].textEdit->document()->isModified())
    {
        int res = QMessageBox::information(this, "TweeEdit Tip",
                                           tr("This file is <b>unsaved</b>.\nDo you want save it ?"),
                                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (res == QMessageBox::Cancel)
            return;
        else if (res == QMessageBox::Yes)
            saveDocument();
    }

    totalText--;

    tabWidget->removeTab(currentText);
    document.removeAt(currentText + 1);

    if (totalText == 0)
        setEnableActions(false);

    statuBar->showMessage(tr("You have just closed a text document!"), 3000);
}

void MainWindow::saveAsDocument()
{
    qDebug() << "SaveAs called\n";
    qDebug() << "The path of the current file you want to save: " << document[currentText].textPath << "\n";
    qDebug() << "Is first create? " << document[currentText].bFirstCreate << "\n";
    qDebug() << "saveDocument called, currentText: " << currentText << "\n";

    // gets the text of the current file
    const QString text = document[currentText].textEdit->toPlainText();
    qDebug() << "The text of the current file: " << text << "\n";

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

    QFileInfo info(file);
    tabWidget->setTabText(currentText, info.fileName());
    file.close();

    document[currentText].textEdit->document()->setModified(false);
    document[currentText].bFirstCreate = false;

    statuBar->showMessage(tr("Save file successfully"), 3000);
}

// special 'file' slots

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
                                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (res == QMessageBox::Cancel)
            return;
        else if (res == QMessageBox::Yes)
            saveSelectedDocument(index);
    }

    totalText--;
    tabWidget->removeTab(index);
    document.removeAt(index);

    if (totalText == 0)
        setEnableActions(false);

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

    printer=nullptr;
    printDialog=nullptr;
}
