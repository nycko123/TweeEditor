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
#include <QFontDialog>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.h"

// basic
void MainWindow::getCurrentPage()
{
    currentText = tabWidget->currentIndex();
    qDebug() << "currentText: " << currentText << "\n";
}

// 'edit'
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

// 'help'
void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::aboutThisApp()
{
    const QString introduce = "This program is an open-source application.\nMade by TweeChalice.";
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    messageBox->setIcon(QMessageBox::Icon::Information);
    messageBox->setText(introduce);
    messageBox->setWindowTitle(tr("About TweeEditor"));
    messageBox->setDefaultButton(QMessageBox::Ok);
    messageBox->show();
}
