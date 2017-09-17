#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

void initLocalization()
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
}

void initSettings(const QString &fileName)
{

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initLocalization();

    MainWindow w;
    w.show();

    return a.exec();
}
