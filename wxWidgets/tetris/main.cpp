 /**
 *  main.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://zetcode.com/gui/wxwidgets/thetetrisgame/

#include "main.h"
#include "Tetris.h"


 /**
 *  MyApp: OnInit()
 */
bool MyApp::OnInit()
{
    srand(time(NULL));
    Tetris *tetris = new Tetris(wxT("Tetris"));
    tetris->Centre();
    tetris->Show(true);

    return true;
}


IMPLEMENT_APP(MyApp)
