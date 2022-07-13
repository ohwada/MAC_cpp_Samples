 /**
 * hello_win.cpp
 * 2022-06-01 K.OHWADA
 */

// display HelloWindow using wxFrame

// reference : https://vivacocoa.jp/cpp/wxwidgets/wxwidgets_firststep.php

// g++ hello_win.cpp -std=c++11 `wx-config --cppflags --libs` -o hello_win

#include <wx/wx.h>


 /**
 * class Hello
 */
class Hello : public wxFrame
{
public:
    Hello();
};


 /**
 * Hello: constractor
 */
Hello::Hello() : wxFrame(NULL, -1, wxT("wxWidgets: Hello!") )
{
    // none
}


 /**
 * class App
 */
class App : public wxApp
{
public:
    virtual bool OnInit();
};


 /**
 *  App: OnInit
 */
bool App::OnInit()
{
    Hello *hello = new Hello();
    hello->Show();
    
    return true;
}


IMPLEMENT_APP(App)
