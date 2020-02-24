#include "mainwindow.h"
#include "tweefirstusedialog.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow;

    w->setFont(QFont("Microsoft YaHei"));
    w->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    w->showMaximized();

    QSettings checkFirstUse("TweeLinhk Team", "TweeTextEditor");
    bool firstUse=checkFirstUse.value("firstUse",true).toBool();

    if(firstUse)
    {
        TweeFirstUseDialog *dialog=new TweeFirstUseDialog(w);
        dialog->show();

        checkFirstUse.setValue("firstUse",false);
    }

    return a.exec();
}
