#ifndef TWEEFIRSTUSEDIALOG_H
#define TWEEFIRSTUSEDIALOG_H

#include <QDialog>

class QTextEdit;
class QRadioButton;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class TweeFirstUseDialog : public QDialog
{
    Q_OBJECT

private slots:
    void setAcStatu();  // agree
    void setDisStatu(); // disagree

public:
    TweeFirstUseDialog(QWidget *parent = nullptr);

private:
    bool readLicense();

private:
    QTextEdit *introduce;
    QTextEdit *licenseDisplay;
    QRadioButton *acceptLic;
    QRadioButton *disagreeLic;
    QPushButton *cancel;
    QPushButton *ok;

    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;
};

#endif
