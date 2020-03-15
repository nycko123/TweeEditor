#include "mainwindow.h"
#include <QDebug>

void MainWindow::zoomIn() {
    if (!totalText)
        return;
    zoomFactor++;
    document[currentText].textEdit->zoomIn(zoomFactor);

    qDebug()<<"Zoom factor: "<<zoomFactor<<"\n";
}

void MainWindow::zoomOut() {
    if (zoomFactor <= 1 || !totalText)
        return;

    zoomFactor--;
    document[currentText].textEdit->zoomOut(zoomFactor);

    qDebug()<<"Zoom factor: "<<zoomFactor<<"\n";
}