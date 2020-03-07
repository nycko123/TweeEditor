#include "mainwindow.h"
#include "TweeFirstUseDialog.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSettings settings("TweeApp", "TweeTextEditor");

    // reads the displaying of the language
    //QString language = settings.value("language", EN_US).toString();

    // installs the language
    // bool res;
    // QTranslator translation;
    // if (language == ZH_CN)
    //     res = translation.load(":/TweeSimpleEdit_zh_CN.qm");
    // else if (language == PL_PL)
    //     res = translation.load(":/TweeSimpleEdit_pl_PL.qm");
    // app.installTranslator(&translation);
    // qDebug() << res << "\n";
    // qDebug() << "Selected language:" << language << "\n";

    MainWindow *w = new MainWindow;

    //w->languageDisplayed(language);
    w->setFont(QFont("Microsoft YaHei"));
    w->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    w->showMaximized();

    // checks if you're using it for the first time
    bool firstUse = settings.value("firstUse", true).toBool();

    if (firstUse)
    {
        TweeFirstUseDialog *dialog = new TweeFirstUseDialog(w);
        dialog->show();

        settings.setValue("firstUse", false);
    }

    return app.exec();
}
