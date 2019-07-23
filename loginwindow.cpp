#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_lineEditLogin_returnPressed()
{
    this->HandleLogin();
}

void LoginWindow::on_lineEditPassword_returnPressed()
{
    this->HandleLogin();
}

void LoginWindow::on_pushButtonCancel_clicked()
{
    QString message = "Access Denied";
    this->DisplayMessageBox(message);
    this->close();
}

void LoginWindow::on_pushButtonOk_clicked()
{
   this->HandleLogin();
}

void LoginWindow::DisplayMessageBox(QString message, QString buttonMessage){
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.addButton(buttonMessage, QMessageBox::ButtonRole::AcceptRole);
    msgBox.exec();
}

void LoginWindow::HandleLogin(){
    QString user = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();

    if (!user.isEmpty() && !password.isEmpty()){
        if (this->ValidateCredentials(user, password)){
            this->DisplayMessageBox("Welcome", "Ok");
            this->hide();
            return;
        }
    }

    this->DisplayMessageBox("Username and/or password mismatch");
}

QJsonObject LoginWindow::LoadCredentialsJSON(){
    QFile credentialFile(":/res/credentials.json");
    credentialFile.open(QIODevice::ReadOnly);

    QTextStream input(&credentialFile);
    QString jsonString = input.readAll();
    credentialFile.close();

    QByteArray jsonBytes = jsonString.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes);
    return jsonDoc.object();

}


bool LoginWindow::ValidateCredentials(QString user, QString password){
    QJsonObject users = this->LoadCredentialsJSON();

    if (users.contains(user)){
        if (users.value(user) == password){
            return true;
        }
    }
    return false;
}
