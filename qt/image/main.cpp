/**
 * main.cpp
 * 2022-06-01 K.OHWADA
 */


#include <QtWidgets/QApplication>
#include <iostream>
#include <string>
#include "MainWindow.h"
#include "MyGraphicsView.h"
#include "file_util.hpp"
#include "parse_filename.hpp"

using namespace std;


/**
 * main
 */
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    string fpath = "images/uparrow.png";

    if(argc == 2) {
        fpath = argv[1];
    }

    if( ! existsFile(fpath) )
    {
        cerr << "not find: " << fpath << endl;
        return EXIT_FAILURE;
    }

    string fname = getFileNameWithExt(fpath);

    MainWindow *mainWin = new MainWindow();
  
    MyGraphicsView *view =  new MyGraphicsView();

    QImage image;
    bool ret = image.load( fpath.c_str() );

    if(!ret){
        cerr << "cannot load: " << fpath << endl;
        return EXIT_FAILURE;
    }

   int img_w = image.width();
   int img_h = image.height();

    view->setImg( image );

// display in half size
    mainWin->setGeometry(10, 10, img_w/2, img_h/2);

   mainWin->setWindowTitle( fname.c_str() );

    mainWin->setCentralWidget(view);

    mainWin->show();
        
    return app.exec();
}

