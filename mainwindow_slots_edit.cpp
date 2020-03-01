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
    QFontDialog *fontDialog=new QFontDialog(textFont,this);
    fontDialog->setFont(QFont("Microsoft YaHei"));
    fontDialog->setWindowIcon(this->windowIcon());
    fontDialog->setWindowTitle(tr("Select the font"));
    fontDialog->setCurrentFont(this->textFont);


    if (fontDialog->exec()==QDialog::Accepted)
    {
        textFont = fontDialog->selectedFont();

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

void MainWindow::selectLanguage()
{
    languageDialog=new TweeLanguageDialog(selectedLanguage,this);

    if(languageDialog->exec()==QDialog::Accepted)
    {
        selectedLanguage=languageDialog->selectedLanguage();
        qDebug()<<"Selected language: "<<selectedLanguage<<"\n";

        int res=QMessageBox::information(this,tr("You\'ve changed the displaying of TweeEditor"),
                                           tr("It needs <b>restart</b>. \nNow?"),
                                           QMessageBox::Yes|QMessageBox::No
                                           );
        if(res==QMessageBox::Yes)
            this->close();
    }
}
