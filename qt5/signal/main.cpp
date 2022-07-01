/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

#include <QApplication>
#include "example.h"


/**
 * main
 */
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Example w;    

    w.show();  

    return a.exec();
}

