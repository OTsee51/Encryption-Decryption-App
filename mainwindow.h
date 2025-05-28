#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qaesencryption.h"
#include <QMessageAuthenticationCode>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Explorer_button_clicked();
    void on_Encrypt_button_clicked();
    void on_Decrypt_button_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QByteArray generateSalt(int length);
    QByteArray pbkdf2(const QByteArray &password, const QByteArray &salt, int iterations, int dkLen);
};
#endif // MAINWINDOW_H
