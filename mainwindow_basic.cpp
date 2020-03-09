#include <QtWidgets>

#include "mainwindow.h"

// basic
void MainWindow::getCurrentPage() {
    currentText = tabWidget->currentIndex();
    qDebug() << "currentText: " << currentText << "\n";

    // updates encoding-selecting combo-box
    if (currentText >= 0)
        selectTextCode->setCurrentText(document[currentText].textCode->name());
}

void MainWindow::setEnableWidgets(bool isEnabled) {
    save->setEnabled(isEnabled);
    saveAs->setEnabled(isEnabled);
    closeTab->setEnabled(isEnabled);
    //encodingAction->setEnabled(isEnabled);
    printPage->setEnabled(isEnabled);

    addTime->setEnabled(isEnabled);
    addFileName->setEnabled(isEnabled);
    findText->setEnabled(isEnabled);

    selectTextCode->setEnabled(isEnabled);
}

void MainWindow::setTextEncoding(const QString &encode) {
    auto &currentDocument = document[currentText];

    // checks if encode equals Document::textCode (nothing changed)
    if (currentDocument.textCode->name() == encode)
        return;

    QByteArray encodeData;
    QString decodeStr;
    auto *converterStatu = new QTextCodec::ConverterState(QTextCodec::ConversionFlag::DefaultConversion);

    currentDocument.textCode = QTextCodec::codecForName(encode.toLocal8Bit());
    qDebug() << currentDocument.textCode->name().constData() << "\n";

    auto convertMessage = QString();

    // convert
    retry:
    encodeData = currentDocument.textEdit->toPlainText().toLocal8Bit();
    decodeStr = currentDocument.textCode->toUnicode(encodeData.constData(), encodeData.size(), converterStatu);

    currentDocument.textEdit->setPlainText(decodeStr);

    // shows if it is error converting
    if (converterStatu->invalidChars)
        convertMessage = tr("Error converting this document!");
    else if (converterStatu->remainingChars)
        convertMessage = tr("Some chars that can\'t convert remaining in this document!");

    // some errors occurred
    if (!convertMessage.isEmpty()) {
        int result = 0;
        if (converterStatu->invalidChars)
            result = QMessageBox::critical(this, tr("Error!"), convertMessage, QMessageBox::Retry | QMessageBox::Ok);
        else
            result = QMessageBox::warning(this, tr("Oops!"), convertMessage, QMessageBox::Retry | QMessageBox::Ok);

        if (result == QMessageBox::Retry)
            goto retry;
    } else
        statuBar->showMessage(tr("Translating successfully, please save this document"), 4000);
}