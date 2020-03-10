#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QVector>
#include <QTextCodec>
#include <utility>
#include "FindDialog.h"
#include "TweeLanguageDialog.h"

// the information and the widget of the text document
struct Document {
    QPlainTextEdit *textEdit = nullptr;
    bool bFirstCreate = true; // creates the document for the first time
    QString textPath = "";
    QTextCodec *textCode = QTextCodec::codecForName("UTF-8");

    explicit Document(QPlainTextEdit *widget = new QPlainTextEdit, QString path = "", const bool first = true)
            : textEdit(
            widget), textPath(std::move(path)), bFirstCreate(first) {}
};

class QMenuBar;

// class QToolBar;

class QAction;

class QStatusBar;

class QTabWidget;

class QComboBox;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override = default;

private:
    // basic functions
    void setEnableWidgets(bool); // enables actions in need ?

    // oncreate
    void createActions();           // creates the basic actions
    void createMenuBar();           // creates the menu
    void setEncodings();            // sets encodings
    void createStatuBar();          // creates the state bar
    void createTextEdit();          // creates the text editor window
    void createContextMenu();       // creates context menu
    void readSettingsFromSystem();  // reads settings from the system
    void writeSettingsFromSystem(); // writes settings to the system

private slots:

    // basic functions
    void getCurrentPage();      // gets current QPlainText
    void setTextEncoding(const QString &);    // sets the encoding of all the text

    // common 'file' slots
    void newDocument(const QByteArray &text = "", const QString &title = "untitled.txt", const QString &textPath = "");

    void openDocument();   // opens a text documnet
    void saveDocument();   // saves the text document
    void saveAsDocument(); // the dialog of 'Save As'
    void closeDocument();

    // special 'file' slots
    void saveAsSelectedDocument(int index = -1); // only use when close the other tab
    void saveSelectedDocument(int index = -1);   // only use when close the other tab
    void closeSelectedDocument(int index = -1);

//   void focusEncodingComboBox();
    void
    printCurrentDocument(); // connects to the printer and print current page                                                                                       // closes current tab

    // 'edit' slots
    void addTimetoEdit();

    void addFileNametoEdit();

    void fontSelect();

    void findTextDialog();

    void selectLanguage();

    // 'help' slots
    void aboutQt();

    void aboutThisApp();

protected:
    // mainwindow_events
    void closeEvent(QCloseEvent *event) override;

private:
    QMenuBar *mainMenu{};
    // QToolBar *toolBar{};
    QStatusBar *statuBar{};

    QTabWidget *tabWidget{};
    QVector<Document> document;

    // 'file' actions
    QAction *newText{};
    QAction *open{};
    QAction *save{};
    QAction *saveAs{};
    QAction *encodingAction{};
    QAction *printPage{};
    QAction *closeTab{};
    QAction *exitApp{};

    // 'edit' actions
    QAction *addTime{};
    QAction *addFileName{};
    QAction *findText{};
    QAction *font{};
    QAction *displayLanguage{};

    // 'help' actions
    QAction *aboutQtAction{};
    QAction *aboutThisAppAction{};

    // 'edit' dialogs
    TweeFindDialog *findDialog{};
    TweeLanguageDialog *languageDialog{};

    int currentText = 0;
    int countText = 0;
    int totalText = 0; // records the number of QPlainText created

    // the displaying of the text
    QFont textFont;
    // the displaying language of the application
    QString selectedLanguage;

    QAction *seperator{};

    // for the statu-bar
    QComboBox *selectTextCode{};
};

#endif // MAINWINDOW_H
