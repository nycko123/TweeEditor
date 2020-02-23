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
    QPlainTextEdit *textEdit;
    bool bFirstCreate = true; // creates the document for the first time
    bool bSave = false;
    QString textPath;

    Document(QPlainTextEdit *widget = new QPlainTextEdit, const QString path = "", const bool first = true, const bool save = false) : textEdit(widget), textPath(path), bFirstCreate(first), bSave(save) {}
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
    void readSettings(); // reads JSON settings
    ~MainWindow() = default;

private:
    void createActions();     // creates the basic actions
    void createMenuBar();     // creates the menu
    void createStatuBar();    // creates the state bar
    void createTextEdit();    // creates the text editor window
    void createContextMenu(); // creates context menu

    void readSettingsFromSystem();  // reads settings from the system
    void writeSettingsFromSystem(); // writes settings to the system

private slots:

    // 'file' slots
    void getCurrentPage();                                                                                           // gets current QPlainText
    void newDocument(const QString &text = "", const QString &title = "untitled.txt", const QString &textPath = ""); // displays a new text documnet
    void openDocument();                                                                                             // opens a text documnet
    void saveDocument();                                                                                             // saves the text document
    void saveAsDocument();                                                                                           // the dialog of 'Save As'
    void closeDocument();                                                                                            // closes current tab

    // 'edit' slots
    void addTimetoEdit();
    void addFileNametoEdit();
    void fontSelect();
    void findTextDialog();

    // 'help' slots
    void aboutQt();
    void aboutThisApp();

    // other slots (special_events.cpp)
    void saveAsSelectedDocument(int index = -1); // only use when close the other tab
    void saveSelectedDocument(int index = -1);   // only use when close the other tab
    void closeSelectedDocument(int index = -1);

protected:
    // special_events
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
    int totalText = 0; // records the number of QPlainText created

    // the displaying of the text
    QFont textFont;
};
#endif // MAINWINDOW_H
