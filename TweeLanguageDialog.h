#ifndef TWEELANGUAGEDIALOG_H
#define TWEELANGUAGEDIALOG_H

#define ZH_CN "简体中文"        // chinese
#define EN_US "English"        // english
#define PL_PL "Polski"         // polish

#include <QDialog>
#include <QDialogButtonBox>

class QComboBox;
class QLabel;

class TweeLanguageDialog : public QDialog
{
    Q_OBJECT

public:
    TweeLanguageDialog(const QString &currentLanguage,QWidget *parent=nullptr);

    QString selectedLanguage() const;

private slots:
    void updateSelection();

private:
    QComboBox *languageBox;

    // saves the selected translation
    QString selectLanguage="";

    QDialogButtonBox *buttonBox;

};

#endif // TWEELANGUAGEDIALOG_H
