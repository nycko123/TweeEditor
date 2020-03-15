#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextDocument>

#define FIND_WHOLEWORD QTextDocument::FindWholeWords
#define FIND_INCASESENTIVILY QTextDocument::FindFlags()
#define FIND_CASESENTIVILY QTextDocument::FindCaseSensitively
#define FIND_BACKWARD QTextDocument::FindBackward

class QPushButton;

class QLineEdit;

class QPlainTextEdit;

class QRadioButton;

class QCheckBox;

class TweeFindDialog : public QDialog {
Q_OBJECT

private slots:

    void findEnteredText(); // when button 'ok' clicks
    void findIncase();      // presses the 'findIn...' radio button
    void findWhole();       // presses the 'findWord' radio button
    void findBack();        // presses the 'findBackward' radio button
    void findCase();        // presses the 'findCase...' radio button

    void setRegular();      // presses the 'findRegular...' radio button

public:
    explicit TweeFindDialog(QPlainTextEdit *textEdit, QWidget *parent = nullptr);

private:
    QLineEdit *findText{};
    QPushButton *cancel{};
    QPushButton *ok{};
    QPlainTextEdit *currentTextEdit{};
    QWidget *parent{};

    // the way to find the word
    QRadioButton *findWholeWord{};
    QRadioButton *findForward{};
    QRadioButton *findBackward{};

    // extra finding options
    QRadioButton *findIncaseSensitively{};
    QRadioButton *findCaseSensitively{};

    // special finding options
    QRadioButton *findRegularExpression{};

    QTextDocument::FindFlags findWay = FIND_INCASESENTIVILY;
    bool bFindRegular = false;
};

#endif
