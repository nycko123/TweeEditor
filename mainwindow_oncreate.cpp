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

#include "mainwindow.h"

// on create the window

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    readSettings();
    createActions();
    createMenuBar();
    createContextMenu();
    createStatuBar();
    createTextEdit();
}

void MainWindow::readSettings()
{
//     const QString display_settings("\\settings\\display_settings.json");
//     QFile settingsFile(display_settings);
// retry:
//     if (!settingsFile.open(QIODevice::ReadOnly))
//     {
//         int res = QMessageBox::critical(this, tr("Error"),
//                                         tr("Error opening JSON file!"), QMessageBox::Retry, QMessageBox::Ok);
//         if (res == QMessageBox::Retry)
//             goto retry;
//         return;
//     }
//     QJsonDocument display_settings_document(QJsonDocument::fromJson(settingsFile.readAll()));
//     QJsonObject obj = display_settings_document.object();
//     QFont globalFont(obj.value("global_font").toString());
//     this->setFont(globalFont);
}

void MainWindow::createActions()
{
    // sets up
    newText = new QAction(QIcon(":/ico/new.png"), tr("New"));
    open = new QAction(QIcon(":/ico/open.png"), tr("Open"));
    save = new QAction(QIcon(":/ico/save.png"), tr("Save"));
    saveAs = new QAction(QIcon(":/ico/save.png"), tr("Save As"));
    closeTab = new QAction(QIcon(":/ico/closeTab.jpg"), tr("Close"));
    exitApp = new QAction(tr("Exit"));

    font = new QAction(tr("Font"));
    findText = new QAction(tr("Find"));

    aboutQtAction = new QAction(QIcon(":/ico/Qt.jpg"), tr("About Qt"));
    aboutThisAppAction = new QAction(QIcon(":/ico/TweeEditor.jpg"), tr("About TweeEditor"));

    newText->setShortcut(QKeySequence::New);
    open->setShortcut(QKeySequence::Open);
    save->setShortcut(QKeySequence::Save);
    saveAs->setShortcut(QKeySequence::SaveAs);
    closeTab->setShortcut(tr("Ctrl+W"));
    exitApp->setShortcut(tr("Ctrl+Q"));

    font->setShortcut(tr("Ctrl+S+F"));
    findText->setShortcut(QKeySequence::Find);

    newText->setStatusTip(tr("Create a new text"));
    save->setStatusTip(tr("Save the current file"));
    saveAs->setStatusTip(tr("Save a document as another file"));
    open->setStatusTip(tr("Open a text file"));
    closeTab->setStatusTip(tr("Close current tab"));

    font->setStatusTip(tr("Sets the global text"));
    findText->setStatusTip(tr("Find the text"));

    save->setEnabled(false);
    saveAs->setEnabled(false);
    closeTab->setEnabled(false);
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

    connect(font,SIGNAL(triggered()),this,SLOT(fontSelect()));
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

    this->addAction(seperator);

    this->addAction(closeTab);
    this->addAction(exitApp);

    this->addAction(seperator);

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
    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeDocument(int)));
}
