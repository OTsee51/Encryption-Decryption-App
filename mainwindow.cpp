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
    setWindowTitle("Encryption/Decryption");
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->decryptPasswordEdit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Генерация соли
QByteArray MainWindow::generateSalt(int length)
{
    QByteArray salt;
    salt.resize(length);
    QRandomGenerator *generator = QRandomGenerator::global();
    for (int i = 0; i < length; i++) {
        salt[i] = static_cast<char>(generator->bounded(256));
    }
    return salt;
}

// Реализация PBKDF2.
QByteArray MainWindow::pbkdf2(const QByteArray &password, const QByteArray &salt, int iterations, int dkLen) {
    if (dkLen <= 0) return QByteArray();

    const int hashLen = 32;
    int blockCount = (dkLen + hashLen - 1) / hashLen;
    QByteArray dk;

    for (int i = 1; i <= blockCount; i++) {
        QByteArray block = salt;
        block.append(static_cast<char>((i >> 24) & 0xFF));
        block.append(static_cast<char>((i >> 16) & 0xFF));
        block.append(static_cast<char>((i >> 8) & 0xFF));
        block.append(static_cast<char>(i & 0xFF));

        QByteArray U = QMessageAuthenticationCode::hash(block, password, QCryptographicHash::Sha256);
        QByteArray T = U;

        for (int j = 1; j < iterations; j++) {
            U = QMessageAuthenticationCode::hash(U, password, QCryptographicHash::Sha256);
            for (int k = 0; k < T.size(); k++) {
                T[k] = T[k] ^ U[k];
            }
        }
        dk.append(T);
    }
    return dk.left(dkLen);
}

void MainWindow::on_Explorer_button_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Select File", QDir::homePath(), "All Files (*)");
    if(!fileName.isEmpty()) {
        ui->Explorer_button->setText("Selected: " + QFileInfo(fileName).fileName());
    }
}

void MainWindow::on_Encrypt_button_clicked()
{
    if(fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "File is Empty");
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


    QByteArray salt = generateSalt(16);
    QByteArray dk = pbkdf2(password.toUtf8(), salt, 10000, 48);
    QByteArray key = dk.left(32);
    QByteArray iv = dk.mid(32, 16);

    QByteArray fileData = inputFile.readAll();
    inputFile.close();

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
    QByteArray encrypted = aes.encode(fileData, key, iv);

    QString outputFile = fileName + ".enc";
    QFile encryptedFile(outputFile);
    if(!encryptedFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", "Can't create encrypted file!");
        return;
    }
    encryptedFile.write(salt);
    encryptedFile.write(encrypted);
    encryptedFile.close();

    QMessageBox::information(this, "Success!",
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

    // Проверка на мін. размер файла
    if(inputFile.size() < 16) {
        QMessageBox::critical(this, "Error", "Invalid file format!");
        inputFile.close();
        return;
    }

    QByteArray salt = inputFile.read(16);
    QByteArray encryptedData = inputFile.readAll();
    inputFile.close();

    QByteArray dk = pbkdf2(password.toUtf8(), salt, 10000, 48);
    QByteArray key = dk.left(32);
    QByteArray iv = dk.mid(32, 16);

    QAESEncryption aes(QAESEncryption::AES_256, QAESEncryption::CBC);
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

    QMessageBox::information(this, "Success!",
                             "File decrypted successfully!\nSaved as: " + outputFile);
}
