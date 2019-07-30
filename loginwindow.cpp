#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow),
    translator(new QTranslator)
{
    ui->setupUi(this);
    this->HandleLanguageChange(ui->comboBoxLocales->currentText());
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete translator;
    // 'browser' does not need to be deleted since it includes 'setAttribute(Qt::WA_DeleteOnClose, true);'.
    // I think.
}

void LoginWindow::on_comboBoxLocales_currentIndexChanged(const QString &selectedLocale)
{
    this->HandleLanguageChange(selectedLocale);
}

void LoginWindow::on_pushButtonCancel_clicked()
{
    this->DisplayMessageBox(tr("Access Denied"));
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

void LoginWindow::HandleLanguageChange(QString selectedLocale)
{
    QStringList locales = { "dk", "en" };

    switch (locales.indexOf(selectedLocale.toLower()))
    {
        case 0:
        translator->load(":/res/login_dk.qm");
        qApp->installTranslator(translator);
        break;

        case 1:
        translator->load("");
        break;
    }
    ui->retranslateUi(this);
}

void LoginWindow::HandleLogin(QString user, QString password)
{
    bool validated = !user.isEmpty() && !password.isEmpty() ? this->ValidateCredentials(user, password) : false;

    if (validated)
    {
        this->DisplayMessageBox(tr("Welcome"), tr("Ok"));

        //passing in default nullptr to BrowserWindow so it's top level and will minimize to taskbar instead of parent.
        browser = new BrowserWindow();
        browser->resize(QGuiApplication::primaryScreen()->size() * 0.7);
        browser->show();
        this->hide();
    }
    else
    {
        this->DisplayMessageBox(tr("Username and/or password mismatch"));
    }

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


