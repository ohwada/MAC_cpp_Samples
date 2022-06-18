/**
 * pushubotton.cpp
 * window with pushubotton
 * 2022-06-01 K.OHWADA
 */


// reference : https://www.webcyou.com/?p=10610

#include <QtWidgets/QApplication>
#include <QPushButton>
 

/**
 * main
 */
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    QPushButton *button = new QPushButton("Quit");

    QObject::connect( button, SIGNAL(clicked()), &app, SLOT(quit()) );

    button->show();

    return app.exec();
}

