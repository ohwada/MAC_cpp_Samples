/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */

// refference : https://www.webcyou.com/?p=10610


#include <QtWidgets/QApplication>
 
#include "finddialog.h"
 

/**
 * main
*/
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    FindDialog *dialog = new FindDialog;
    dialog->show();
    return app.exec();
}
