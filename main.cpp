#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.readSettings();
    w.setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    w.showMaximized();
    return a.exec();
}
