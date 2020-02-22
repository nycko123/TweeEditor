#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;
    w->setFont(QFont("Microsoft YaHei"));
    w->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    w->showMaximized();
    return a.exec();
}
