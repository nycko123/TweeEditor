#include "mainwindow.h"
#include "TweeFirstUseDialog.h"

#include <QApplication>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    new QApplication(argc, argv);

    QSettings settings("TweeApp", "TweeTextEditor");

    QString language = settings.value("language", EN_US).toString();
    // loads the translation
    bool res = true;

    // installs the language translation

    QTranslator translation;
    if (language == ZH_CN) {
        res = translation.load(":/TweeSimpleEdit_zh_CN.qm");
        qDebug() << "Loading TweeSimpleEdit_zh_CN.qm" << "\n";
    } else if (language == PL_PL) {
        res = translation.load(":/TweeSimpleEdit_pl_PL.qm");
        qDebug() << "Loading TweeSimpleEdit_pl_PL.qm" << "\n";
    }

    // loads
    QApplication::installTranslator(&translation);

    qDebug() << res << "\n";
    qDebug() << "Selected language:" << language << "\n";

    if (!res)
        // error occurred!
        QMessageBox::critical(nullptr, QObject::tr("Error collecting data!"),
                              QObject::tr("Loading translation failed!"), QMessageBox::Ok);


    auto *w = new MainWindow(nullptr, language);

    w->setFont(QFont("Microsoft YaHei"));
    w->setWindowIcon(QIcon(":/ico/TweeEditor.jpg"));
    w->showMaximized();

    // checks if you're using it for the first time
    bool firstUse = settings.value("firstUse", true).toBool();

    if (firstUse) {
        auto *dialog = new TweeFirstUseDialog(w);
        dialog->show();

        settings.setValue("firstUse", false);
    }

    return QApplication::exec();
}