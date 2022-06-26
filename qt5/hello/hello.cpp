/**
 * hello.cpp
 * hello window
 * 2022-06-01 K.OHWADA
 */

// refference : https://www.webcyou.com/?p=10581

#include <QApplication>
#include <QLabel>

/**
 * main
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

 QLabel *label = new QLabel("Hello World!");
    label->show();

    return app.exec();
}

