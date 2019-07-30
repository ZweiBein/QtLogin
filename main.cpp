#include "loginwindow.h"
#include <QApplication>
//#include <QTranslator>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    //QTranslator translator;

    //a.installTranslator(&translator);
    LoginWindow w;
    w.show();

    return a.exec();
}
