#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>


#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("ENS","Climate-Model");
    settings.value("lang","en");

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.setWindowTitle("Climate-Model");
    w.showMaximized();

    return a.exec();
}
