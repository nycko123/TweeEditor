#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVector>
#include "FindDialog.h"

constexpr int MAX_QPLAINTEXT = 11;

// the information and the widget of the text document
struct Document
{
    QPlainTextEdit *textEdit=nullptr;
    bool bFirstCreate = true; // creates the document for the first time
    QString textPath="";

    Document(QPlainTextEdit *widget = new QPlainTextEdit, const QString path = "", const bool first = true) : textEdit(widget), textPath(path), bFirstCreate(first) {}
};

class QMenuBar;
class QToolBar;
class QAction;
class QStatusBar;
class QTabWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    // basic functions
    void setEnableActions(bool); // enables actions in need ?

    // oncreate
    void createActions();           // creates the basic actions
    void createMenuBar();           // creates the menu
    void createStatuBar();          // creates the state bar
    void createTextEdit();          // creates the text editor window
    void createContextMenu();       // creates context menu
    void readSettingsFromSystem();  // reads settings from the system
    void writeSettingsFromSystem(); // writes settings to the system

private slots:
    // basic functions
    void getCurrentPage(); // gets current QPlainText

    // common 'file' slots
    void newDocument(const QString &text = "", const QString &title = "untitled.txt", const QString &textPath = "");
    void openDocument();   // opens a text documnet
    void saveDocument();   // saves the text document
    void saveAsDocument(); // the dialog of 'Save As'
    void closeDocument();

    // special 'file' slots
    void saveAsSelectedDocument(int index = -1); // only use when close the other tab
    void saveSelectedDocument(int index = -1);   // only use when close the other tab
    void closeSelectedDocument(int index = -1);
    void printCurrentDocument(); // connects to the printer and print current page                                                                                       // closes current tab

    // 'edit' slots
    void addTimetoEdit();
    void addFileNametoEdit();
    void fontSelect();
    void findTextDialog();

    // 'help' slots
    void aboutQt();
    void aboutThisApp();

protected:
    // mainwindow_events
    void closeEvent(QCloseEvent *event) override;

private:
    QMenuBar *mainMenu;
    QToolBar *toolBar;
    QStatusBar *statuBar;

    QTabWidget *tabWidget;
    QVector<Document> document;

    // 'file' actions
    QAction *newText;
    QAction *open;
    QAction *save;
    QAction *saveAs;
    QAction *printPage;
    QAction *closeTab;
    QAction *exitApp;

    // 'edit' actions
    QAction *addTime;
    QAction *addFileName;
    QAction *findText;
    QAction *font;

    // 'help' actions
    QAction *aboutQtAction;
    QAction *aboutThisAppAction;

    TweeFindDialog *findDialog;

    int currentText = 0;
    int countText = 0;
    int totalText = 0; // records the number of QPlainText created

    // the displaying of the text
    QFont textFont;
};
#endif // MAINWINDOW_H
