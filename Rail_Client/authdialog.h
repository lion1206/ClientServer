#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    ~AuthDialog();

private slots:
    void on_registerButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::AuthDialog *ui;
};

#endif // AUTHDIALOG_H
