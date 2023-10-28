#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <QRegularExpression>

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
    void on_large_radioButton_clicked();



    void on_medium_radioButton_clicked();

    void on_small_radioButton_clicked();
    void check_Box_checked(bool value);

    void on_pushButton_reset_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_order_clicked();

    void on_firstNameLineEdit_textEdited(const QString &arg1);

    void on_lastNameLineEdit_textEdited(const QString &arg1);

    void on_streetLineEdit_textEdited(const QString &arg1);


    void on_lineEdit_textEdited(const QString &arg1);

    void on_cityLineEdit_textEdited(const QString &arg1);

    void on_postalCodeLineEdit_textEdited(const QString &arg1);


private:
    void validateText(const QString &arg,const QString &regex);
    void validatePostalCode(const QString &arg);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
