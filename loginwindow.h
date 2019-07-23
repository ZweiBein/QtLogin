#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QJsonObject>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonOk_clicked();

private:
    Ui::LoginWindow *ui;
    void HandleLogin();
    void DisplayMessageBox(QString, QString buttonMessage = "Close");
    bool ValidateCredentials(QString, QString);
    QJsonObject LoadCredentialsJSON();
};

#endif // LOGINWINDOW_H
