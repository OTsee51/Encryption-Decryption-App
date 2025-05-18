#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->decryptPasswordEdit->setEchoMode(QLineEdit::Password);
}


MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::generateKey(const QString &password)
{
    // Генерация 256-битного ключа
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
}

QByteArray MainWindow::generateIV(const QString &password)
{
    // Генерация 128-битного IV
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).left(16);
}

void MainWindow::on_Explprer_button_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Select File", QDir::homePath(), "All Files (*)");
    if(!fileName.isEmpty()) {
        ui->Explprer_button->setText("Selected: " + fileName);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(fileName.isEmpty())
    {
        QMessageBox :: warning(this, "Error", "File is Empty");
        return;
    }

    QString password = ui->passwordEdit->text();
    if(password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a password!");
        return;
    }


    QFile inputFile(fileName);
    if(!inputFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Can't open file for reading!");
        return;
    }

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray key = generateKey(password);
    QByteArray iv = generateIV(password);

    QByteArray fileData = inputFile.readAll();
    inputFile.close();

    QByteArray encrypted = aes.encode(fileData, key, iv);

    QString outputFile = fileName + ".enc";
    QFile encryptedFile(outputFile);
    if(!encryptedFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Error", "Can't create encrypted file!");
        return;
    }
    encryptedFile.write(encrypted);
    encryptedFile.close();

    QMessageBox::information(this, "Success",
                    "File encrypted successfully!\nSaved as: " + outputFile);
}





void MainWindow::on_Decrypt_button_clicked()
{
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "File is Empty");
        return;
    }

    QString password = ui->decryptPasswordEdit->text();
    if(password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a password!");
        return;
    }

    QFile inputFile(fileName);
    if(!inputFile.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Can't open file for reading!");
        return;
    }

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray key = generateKey(password);
    QByteArray iv = generateIV(password);

    QByteArray encryptedData = inputFile.readAll();
    inputFile.close();

    QByteArray decrypted = aes.decode(encryptedData, key, iv);
    decrypted = aes.removePadding(decrypted);

    QString outputFile = fileName;
    if(outputFile.endsWith(".enc")) {
        outputFile.chop(4);
    } else {
        outputFile += ".dec";
    }

    QFile decryptedFile(outputFile);
    if(!decryptedFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Can't create decrypted file!");
        return;
    }

    decryptedFile.write(decrypted);
    decryptedFile.close();

    QMessageBox::information(this, "Success",
                             "File decrypted successfully!\nSaved as: " + outputFile);
}

