#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QWebEngineView>
#include <QScreen>

class BrowserWindow;

class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrowserWindow(QWidget *parent = nullptr);
    ~BrowserWindow();

protected slots:
    void SetURL();
    void ChangeLocation();
    void SetTitle();


private:
    QWebEngineView *view;
    QLineEdit *lineEditURL;
    QToolBar *toolbar;

};

#endif // MAINWINDOW_H
