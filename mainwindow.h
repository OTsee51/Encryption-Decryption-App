// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qaesencryption.h"
#include <QCryptographicHash>

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
    void on_Explprer_button_clicked();
    void on_pushButton_2_clicked();
    void on_Decrypt_button_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QByteArray generateKey(const QString &password);
    QByteArray generateIV(const QString &password);
};
#endif // MAINWINDOW_H
