#include <QtWebEngineWidgets>
#include "browserwindow.h"

BrowserWindow::BrowserWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowIcon(QIcon(":/res/Ordbogen.png"));

    view = new QWebEngineView(this);
    view->load(QUrl("https://github.com/ZweiBein/QtLogin"));
    connect(view, &QWebEngineView::loadFinished, this, &BrowserWindow::SetURL);
    connect(view, &QWebEngineView::loadFinished, this, &BrowserWindow::SetTitle);

    lineEditURL = new QLineEdit(this);
    lineEditURL->setSizePolicy(QSizePolicy::Expanding, lineEditURL->sizePolicy().verticalPolicy());
    connect(lineEditURL, &QLineEdit::returnPressed, this, &BrowserWindow::ChangeLocation);

    toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolbar);
    toolbar->setMovable(false);
    toolbar->addWidget(lineEditURL);

    setCentralWidget(view);
}

BrowserWindow::~BrowserWindow()
{

}

void BrowserWindow::ChangeLocation()
{
    QUrl url = QUrl::fromUserInput(lineEditURL->text());
    view->load(url);    
    view->setFocus();    
}

void BrowserWindow::SetTitle()
{
    QString title = view->title().isEmpty() ? "Browser" : view->title();
    setWindowTitle(title);
}

void BrowserWindow::SetURL()
{
    lineEditURL->setText(view->url().toString());
}
