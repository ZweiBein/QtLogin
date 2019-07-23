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

void LoginWindow::on_pushButtonCancel_clicked()
{
    this->DisplayMessageBox("Access Denied");
    this->close();
}

void LoginWindow::on_pushButtonOk_clicked()
{
   QString user = ui->lineEditLogin->text();
   QString password = ui->lineEditPassword->text();
   this->HandleLogin(user, password);
}

void LoginWindow::DisplayMessageBox(QString message, QString buttonMessage)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.addButton(buttonMessage, QMessageBox::ButtonRole::AcceptRole);
    msgBox.exec();
}

void LoginWindow::HandleLogin(QString user, QString password)
{
    if (!user.isEmpty() && !password.isEmpty()){
        if (this->ValidateCredentials(user, password)){
            this->DisplayMessageBox("Welcome", "Ok");
            return;
        }
    }

    this->DisplayMessageBox("Username and/or password mismatch");
}

QJsonObject LoginWindow::LoadCredentialsJSON()
{
    QFile credentialFile(":/res/credentials.json");
    credentialFile.open(QIODevice::ReadOnly);

    QTextStream input(&credentialFile);
    QString jsonString = input.readAll();
    credentialFile.close();

    QByteArray jsonBytes = jsonString.toUtf8();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes);
    return jsonDoc.object();

}


bool LoginWindow::ValidateCredentials(QString user, QString password)
{
    QJsonObject users = this->LoadCredentialsJSON();

    if (users.contains(user)){
        if (users.value(user) == password){
            return true;
        }
    }
    return false;
}
