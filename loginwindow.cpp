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
   QString user = ui->lineEditLogin->text().trimmed();
   QString password = ui->lineEditPassword->text().trimmed();
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
    if (!user.isEmpty() && !password.isEmpty())
    {
        bool validated = this->ValidateCredentials(user, password);
        if (validated)
        {
            this->DisplayMessageBox("Welcome", "Ok");

            //passing in default nullptr to BrowserWindow so it's top level and will minimize to taskbar instead of parent.
            browser = new BrowserWindow();
            browser->resize(QGuiApplication::primaryScreen()->size() * 0.7);
            browser->show();
            this->hide();
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

    if (users.contains(user))
    {
        if (users.value(user) == password)
        {
            return true;
        }
    }
    return false;
}
