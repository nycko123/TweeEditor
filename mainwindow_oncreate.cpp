#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QTabWidget>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QSettings>

#include "mainwindow.h"

// on create the window

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    readSettingsFromSystem();
    createActions();
    createMenuBar();
    createContextMenu();
    createStatuBar();
    createTextEdit();
}

void MainWindow::createActions()
{
    // sets up
    newText = new QAction(QIcon(":/ico/new.png"), tr("New"));
    open = new QAction(QIcon(":/ico/open.png"), tr("Open"));
    save = new QAction(QIcon(":/ico/save.png"), tr("Save"));
    saveAs = new QAction(QIcon(":/ico/save.png"), tr("Save As"));
    closeTab = new QAction(QIcon(":/ico/closeTab.jpg"), tr("Close"));
    exitApp = new QAction(QIcon(":/ico/exit.jpg"),tr("Exit"));

    addTime=new QAction(QIcon(":/ico/addTime.jpg"),tr("Add time"));
    addFileName=new QAction(QIcon(":/ico/file.png"),tr("Add file name"));
    font = new QAction(QIcon(":/ico/font.jpg"),tr("Font"));
    findText = new QAction(QIcon(":/ico/find.png"), tr("Find"));

    aboutQtAction = new QAction(QIcon(":/ico/Qt.jpg"), tr("About Qt"));
    aboutThisAppAction = new QAction(QIcon(":/ico/TweeEditor.jpg"), tr("About TweeEditor"));

    newText->setShortcut(QKeySequence::New);
    open->setShortcut(QKeySequence::Open);
    save->setShortcut(QKeySequence::Save);
    saveAs->setShortcut(QKeySequence::SaveAs);
    closeTab->setShortcut(tr("Ctrl+W"));
    exitApp->setShortcut(tr("Ctrl+Q"));

    addTime->setShortcut(tr("Alt+T"));
    addFileName->setShortcut(tr("Alt+N"));
    findText->setShortcut(QKeySequence::Find);

    newText->setStatusTip(tr("Create a new text"));
    save->setStatusTip(tr("Save the current file"));
    saveAs->setStatusTip(tr("Save a document as another file"));
    open->setStatusTip(tr("Open a text file"));
    closeTab->setStatusTip(tr("Close current tab"));

    addTime->setStatusTip(tr("Adds the current time to the current page"));
    addFileName->setStatusTip(tr("Adds the current file name to the current page"));
    font->setStatusTip(tr("Sets the global text"));
    findText->setStatusTip(tr("Find the text"));

    save->setEnabled(false);
    saveAs->setEnabled(false);
    closeTab->setEnabled(false);

    addTime->setEnabled(false);
    addFileName->setEnabled(false);
    findText->setEnabled(false);

    aboutQtAction->setStatusTip(tr("The information about Qt."));
    aboutThisAppAction->setStatusTip(tr("About TweeEditor"));

    // connects
    connect(newText, SIGNAL(triggered()), this, SLOT(newDocument()));
    connect(open, SIGNAL(triggered()), this, SLOT(openDocument()));
    connect(save, SIGNAL(triggered()), this, SLOT(saveDocument()));
    connect(saveAs, SIGNAL(triggered()), this, SLOT(saveAsDocument()));
    connect(closeTab, SIGNAL(triggered()), this, SLOT(closeDocument()));
    connect(exitApp, &QAction::triggered, this, &QMainWindow::close);

    connect(addTime,SIGNAL(triggered()),this,SLOT(addTimetoEdit()));
    connect(addFileName,SIGNAL(triggered()),this,SLOT(addFileNametoEdit()));
    connect(font, SIGNAL(triggered()), this, SLOT(fontSelect()));
    connect(findText, SIGNAL(triggered()), this, SLOT(findTextDialog()));

    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(aboutThisAppAction, SIGNAL(triggered()), this, SLOT(aboutThisApp()));
}

void MainWindow::createStatuBar()
{
    statuBar = new QStatusBar;
    this->setStatusBar(statuBar);
    QLabel *label = new QLabel(tr("<i>Ready</i>"));
    statuBar->addWidget(label);
}

void MainWindow::createMenuBar()
{
    // sets up
    // 'file' menu
    QMenu *file = new QMenu(tr("&File"));

    file->addAction(newText);

    file->addSeparator();

    file->addAction(open);
    file->addAction(save);
    file->addAction(saveAs);

    file->addSeparator();

    file->addAction(closeTab);
    file->addAction(exitApp);

    // 'edit' menu
    QMenu *edit = new QMenu(tr("&Edit"));

    edit->addAction(addTime);
    edit->addAction(addFileName);

    edit->addSeparator();

    edit->addAction(font);

    edit->addSeparator();

    edit->addAction(findText);

    // 'help' menu
    QMenu *help = new QMenu(tr("&Help"));
    help->addAction(aboutQtAction);
    help->addAction(aboutThisAppAction);

    // sets main menu
    mainMenu = new QMenuBar;
    mainMenu->addMenu(file);
    mainMenu->addMenu(edit);

    mainMenu->addSeparator();

    mainMenu->addMenu(help);
    this->setMenuBar(mainMenu);
}

void MainWindow::createContextMenu()
{
    this->addAction(newText);

    QAction *seperator = new QAction;
    seperator->setSeparator(true);
    this->addAction(seperator);

    this->addAction(open);
    this->addAction(save);
    this->addAction(saveAs);
    this->addAction(closeTab);

    this->addAction(seperator);

    this->addAction(addTime);
    this->addAction(addFileName);
    this->addAction(findText);

    this->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
}

void MainWindow::createTextEdit()
{
    // sets up
    tabWidget = new QTabWidget;

    document.resize(1);
    document.clear();

    // adds QPlainText to QTabWidget
    setCentralWidget(tabWidget);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(getCurrentPage()));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeSelectedDocument(int)));
}

void MainWindow::readSettingsFromSystem()
{
    QSettings appSettings("TweeLinhk Team", "TweeTextEditor");

    // reads font saved in the system
    QString fullFont = appSettings.value("textFont", "Microsoft YaHei").toString();
    QString fontName;
    int fontName_pos = 0;

    for (auto &i : fullFont)
    {
        if (i == ',')
        {
            fontName = fullFont.left(fontName_pos);
            break;
        }
        fontName_pos++;
    }

    textFont = fontName;
    textFont.setPixelSize(appSettings.value("textFont_PixelSize").toInt());
    textFont.setPointSize(appSettings.value("textFont_PointSize").toInt());

    qDebug() << "fullFont: " << fullFont << "\n"
             << "fontName: " << fontName << "\n";
    qDebug() << "TextFont: " << textFont.toString() << "\n";
}

void MainWindow::writeSettingsFromSystem()
{
    QSettings appSettings("TweeLinhk Team", "TweeTextEditor");
    appSettings.setValue("textFont", textFont.toString());
    appSettings.setValue("textFont_PixelSize", textFont.pixelSize());
    appSettings.setValue("textFont_PointSize", textFont.pointSize());

    qDebug() << "TextFont: " << textFont.toString() << "\n";
}