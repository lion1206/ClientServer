#include "authdialog.h"
#include "ui_authdialog.h"
#include "client.h"
#include "maindialog.h"
#include <QMessageBox>

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::on_registerButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (Client::instance()->registerUser(username, password)) {
        QMessageBox::information(this, "Registration", "Registration successful!");
    } else {
        QMessageBox::warning(this, "Registration", "Registration failed.");
    }
}

void AuthDialog::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (Client::instance()->authenticateUser(username, password)) {
        MainDialog *mainDialog = new MainDialog;
        mainDialog->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Login", "Login failed.");
    }
}
