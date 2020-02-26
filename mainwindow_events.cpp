#include <QtWidgets>
#include <QCloseEvent>

#include "mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool bAccept = true;
    for (auto &i : document)
    {
        // Search for each file unsaved
        if (i.textEdit->document()->isModified())
        {
            auto res = QMessageBox::information(this, "TweeEdit Tip",
                                                tr("There\'re <b>some files unsaved</b>.\nAre you sure you want to exit?"),
                                                QMessageBox::Yes | QMessageBox::No);
            if (res == QMessageBox::No)
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
