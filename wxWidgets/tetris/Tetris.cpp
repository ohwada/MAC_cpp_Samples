/**
 *  Tetris.cpp
 * 2022-06-01 K.OHWADA
 */

// https://zetcode.com/gui/wxwidgets/thetetrisgame/

#include "Tetris.h"
#include "Board.h"


/**
 *  constractor
 */
Tetris::Tetris(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(180, 380))
{
  wxStatusBar *sb = CreateStatusBar();
  sb->SetStatusText(wxT("0"));
  Board *board = new Board(this);
  board->SetFocus();
  board->Start();
}

