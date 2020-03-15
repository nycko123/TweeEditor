#include <QtWidgets>

#include "mainwindow.h"

void MainWindow::reportBugs()
{
    bugReportDialog=new TweeBugReportDialog(this);

    // reports the bug in 'Issue' HTML page
    if(bugReportDialog->exec()==QDialog::Accepted)
        QDesktopServices::openUrl(QUrl("https://github.com/TweeChalice/TweeEditor/issues"));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::aboutThisApp() {
    const QString introduce = "<center><img src=\":/ico/TweeEditor-introduction-ico.png\" /></center<br> <h2>This is an open-source application.</h2>\n\n<h3>Made by <i>TweeChalice</i> and <i>Linhk</i></h3>.";
    auto *messageBox = new QMessageBox;
    messageBox->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    messageBox->setText(introduce);
    messageBox->setWindowTitle(tr("About TweeEditor"));
    messageBox->setDefaultButton(QMessageBox::Ok);
    messageBox->show();
}
