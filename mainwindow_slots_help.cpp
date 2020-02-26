#include <QtWidgets>

#include "mainwindow.h"

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::aboutThisApp()
{
    const QString introduce = "This program is an open-source application.\n\nMade by TweeChalice and Linhk.";
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    messageBox->setIcon(QMessageBox::Icon::Information);
    messageBox->setText(introduce);
    messageBox->setWindowTitle(tr("About TweeEditor"));
    messageBox->setDefaultButton(QMessageBox::Ok);
    messageBox->show();
}
