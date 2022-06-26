#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile style(":/style/style.qss");
    style.open(QFile::ReadOnly);
    const QString style_sheet = style.readAll();
    style.close();

    MainWindow w;
    w.setStyleSheet(style_sheet);
    w.show();

    return a.exec();
}
