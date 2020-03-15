#ifndef TWEEBUGREPORTDIALOG_H
#define TWEEBUGREPORTDIALOG_H

#include <QDialogButtonBox>
#include <QDialog>

class QLineEdit;

class QAction;

class QClipboard;

class TweeBugReportDialog : public QDialog {
public:
    TweeBugReportDialog(QWidget *parent = nullptr);

    ~TweeBugReportDialog() = default;

private slots:

    void copy0();

    void copy1();

    void copy2();

    void copy3();

private:
    QDialogButtonBox *buttonBox{};
    QLineEdit *sysNameLineEdit{};
    QLineEdit *sysProductNameLineEdit{};
    QLineEdit *sysProductVersionLineEdit{};
    QLineEdit *sysArchLineEdit{};

    QAction *copyAction{};

    QClipboard *board;
};


#endif //TWEEBUGREPORTDIALOG_H
