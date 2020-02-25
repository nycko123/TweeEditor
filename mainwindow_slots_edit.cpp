#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

#include "mainwindow.h"

void MainWindow::newDocument(const QString &text, const QString &title, const QString &textPath)
{
    bool bEmptyPath = textPath.isEmpty();

    save->setEnabled(true);
    saveAs->setEnabled(true);
    closeTab->setEnabled(true);
    printPage->setEnabled(true);

    addTime->setEnabled(true);
    addFileName->setEnabled(true);
    findText->setEnabled(true);

    // default: put the new widget to the back of the queue
    if (totalText == MAX_QPLAINTEXT - 1)
    {
        statuBar->showMessage(tr("Too full to create!"), 3000);
        QMessageBox::critical(this, tr("Error!"), tr("Can\'t create any document now because it\'s full."), QMessageBox::Ok);
        return;
    }
    totalText++;
    countText++;

    document.push_back(Document());

    document.back().textEdit->setPlainText(text);
    document.back().textPath = textPath;
    if (!bEmptyPath)
    {
        document.back().bFirstCreate = false;
        document.back().bSave = true;
    }
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
        int res = QMessageBox::critical(this, tr("Error!"), tr("Can\'t open this file."), QMessageBox::Retry, QMessageBox::Ok);
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

    document[currentText].bSave = true;
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
                                           QMessageBox::Yes | QMessageBox::No);
        if (res == QMessageBox::Yes)
            saveDocument();
    }

    totalText--;

    tabWidget->removeTab(currentText);
    document.removeAt(currentText + 1);

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

    document[currentText].bSave = true;
    document[currentText].bFirstCreate = false;

    file.close();

    statuBar->showMessage(tr("Save file successfully"), 3000);
}
