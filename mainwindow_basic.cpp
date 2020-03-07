#include <QtWidgets>
#include <QDebug>
#include <QAction>

#include "mainwindow.h"

// basic
void MainWindow::getCurrentPage()
{
    currentText = tabWidget->currentIndex();
    qDebug() << "currentText: " << currentText << "\n";
}

void MainWindow::setEnableActions(bool isEnabled)
{
    save->setEnabled(isEnabled);
    saveAs->setEnabled(isEnabled);
    closeTab->setEnabled(isEnabled);
    printPage->setEnabled(isEnabled);

    addTime->setEnabled(isEnabled);
    addFileName->setEnabled(isEnabled);
    findText->setEnabled(isEnabled);
}

void MainWindow::languageDisplayed(const QString &str)
{
    this->selectedLanguage = str;
}

void MainWindow::setTextEncoding(const QString &encode)
{
    //qDebug()<<"Encoding: "<<text<<"\n";

    QByteArray encodeData;
    QString decodeStr;
    QTextCodec::ConverterState *converterStatu = new QTextCodec::ConverterState(QTextCodec::ConversionFlag::DefaultConversion);

    int res = QMessageBox::question(this, tr("Attention!"),
                                    tr("Save these documents before translating to <b>%1?</b>").arg(encode)
                                    , QMessageBox::Yes | QMessageBox::No);

    if (res == QMessageBox::No)
    {
        selectTextCode->setCurrentText(textCode->name());
        return;
    }

    textCode = QTextCodec::codecForName(encode.toLocal8Bit());
    qDebug() << textCode->name().constData() << "\n";

    int cnt_index = 0;
    for (auto &i : document)
    {
        encodeData = i.textEdit->toPlainText().toLocal8Bit();

        statuBar->showMessage(tr("Ready for translating %1").arg(tabWidget->tabText(cnt_index)), 3000);
        this->saveSelectedDocument(cnt_index++);

        decodeStr = textCode->toUnicode(encodeData.constData(), encodeData.size(), converterStatu);

        // translated was not all success
        if (converterStatu->remainingChars)
            QMessageBox::warning(this, tr("Oops!"), tr("There\'s something remaining with the original encoding!"), QMessageBox::Ok);

        // can not translating at all
        else if (converterStatu->invalidChars)
        {
            QMessageBox::critical(this, tr("Error!"), tr("There\'s something wrong with the original encoding!"), QMessageBox::Ok);
            continue;
        }

        i.textEdit->setPlainText(decodeStr);
    }
}