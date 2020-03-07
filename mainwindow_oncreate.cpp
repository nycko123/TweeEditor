#include <QtWidgets>
#include <QAction>
#include <QFile>
#include <QDebug>
#include <QSettings>

#include "mainwindow.h"

// on create the window

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    readSettingsFromSystem();
    setEncodings();
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
    printPage = new QAction(QIcon(":/ico/printer.png"), tr("Print"));
    closeTab = new QAction(QIcon(":/ico/closeTab.png"), tr("Close"));
    exitApp = new QAction(QIcon(":/ico/exit.png"), tr("Exit"));

    addTime = new QAction(QIcon(":/ico/addTime.png"), tr("Add time"));
    addFileName = new QAction(QIcon(":/ico/file.png"), tr("Add file name"));
    font = new QAction(QIcon(":/ico/font.png"), tr("Font"));
    displayLanguage = new QAction(QIcon(":/ico/selectLanguage.jpg"), tr("Language"));
    findText = new QAction(QIcon(":/ico/find.png"), tr("Find"));

    aboutQtAction = new QAction(QIcon(":/ico/Qt.jpg"), tr("About Qt"));
    aboutThisAppAction = new QAction(QIcon(":/ico/TweeEditor.jpg"), tr("About TweeEditor"));

    newText->setShortcut(QKeySequence::New);
    open->setShortcut(QKeySequence::Open);
    save->setShortcut(QKeySequence::Save);
    saveAs->setShortcut(QKeySequence::SaveAs);
    closeTab->setShortcut(tr("Ctrl+W"));
    exitApp->setShortcut(tr("Ctrl+Q"));

    addTime->setShortcut(tr("F2"));
    addFileName->setShortcut(tr("Alt+F2"));
    findText->setShortcut(QKeySequence::Find);

    newText->setStatusTip(tr("Create a new text"));
    save->setStatusTip(tr("Save the current file"));
    saveAs->setStatusTip(tr("Save a document as another file"));
    open->setStatusTip(tr("Open a text file"));
    printPage->setStatusTip(tr("Print current document"));
    closeTab->setStatusTip(tr("Close current tab"));

    addTime->setStatusTip(tr("Adds the current time to the current page"));
    addFileName->setStatusTip(tr("Adds the current file name to the current page"));
    font->setStatusTip(tr("Sets the global text"));
    displayLanguage->setStatusTip(tr("Sets the displaying of the language"));
    findText->setStatusTip(tr("Find the text"));

    setEnableActions(false);

    aboutQtAction->setStatusTip(tr("The information about Qt"));
    aboutThisAppAction->setStatusTip(tr("About TweeEditor"));

    // connects
    connect(newText, SIGNAL(triggered()), this, SLOT(newDocument()));
    connect(open, SIGNAL(triggered()), this, SLOT(openDocument()));
    connect(save, SIGNAL(triggered()), this, SLOT(saveDocument()));
    connect(saveAs, SIGNAL(triggered()), this, SLOT(saveAsDocument()));
    connect(printPage, SIGNAL(triggered()), this, SLOT(printCurrentDocument()));
    connect(closeTab, SIGNAL(triggered()), this, SLOT(closeDocument()));
    connect(exitApp, &QAction::triggered, this, &QMainWindow::close);

    connect(addTime, SIGNAL(triggered()), this, SLOT(addTimetoEdit()));
    connect(addFileName, SIGNAL(triggered()), this, SLOT(addFileNametoEdit()));
    connect(font, SIGNAL(triggered()), this, SLOT(fontSelect()));
    connect(displayLanguage, SIGNAL(triggered()), this, SLOT(selectLanguage()));
    connect(findText, SIGNAL(triggered()), this, SLOT(findTextDialog()));

    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(aboutThisAppAction, SIGNAL(triggered()), this, SLOT(aboutThisApp()));

    seperator = new QAction;
    seperator->setSeparator(true);
}

void MainWindow::setEncodings()
{
    selectTextCode = new QComboBox(this);

    for (const QByteArray &i : QTextCodec::availableCodecs())
        selectTextCode->addItem(QString(i));

    connect(selectTextCode, &QComboBox::currentTextChanged, this, &MainWindow::setTextEncoding);
}

void MainWindow::createStatuBar()
{
    selectTextCode->setCurrentText("UTF-8");

    statuBar = new QStatusBar;
    this->setStatusBar(statuBar);
    QLabel *label = new QLabel(tr("<i>Ready</i>"));

    statuBar->addWidget(label, 1);

    statuBar->addWidget(selectTextCode);
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
    file->addAction(printPage);

    file->addSeparator();

    file->addAction(closeTab);
    file->addAction(exitApp);

    // 'edit' menu
    QMenu *edit = new QMenu(tr("&Edit"));

    edit->addAction(addTime);
    edit->addAction(addFileName);

    edit->addSeparator();

    edit->addAction(font);
    edit->addAction(displayLanguage);

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
    QSettings appSettings("TweeApp", "TweeTextEditor");

    // reads font saved in the system
    QVariant font_settings = appSettings.value("textFont", "Microsoft YaHei");

    textFont = font_settings.value<QFont>();
}

void MainWindow::writeSettingsFromSystem()
{
    QSettings appSettings("TweeApp", "TweeTextEditor");
    appSettings.setValue("textFont", textFont);
    appSettings.setValue("language", selectedLanguage);

    qDebug() << "TextFont: " << textFont.toString() << "\n";
    qDebug() << "Selected language: " << selectedLanguage << "\n";
}
