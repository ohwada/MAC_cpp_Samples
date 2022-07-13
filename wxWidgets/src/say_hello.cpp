 /**
 *  say_hello.cpp
 * 2022-06-01 K.OHWADA
 */

// display "Hello" on Terminal(std out)

// reference : https://vivacocoa.jp/cpp/wxwidgets/wxwidgets_concern.php

// g++ say_hello.cpp -std=c++11 `wx-config --cppflags --libs` -o say_hello


#include <iostream>
#include <wx/wx.h>


 /**
 *  class App
 */
class App : public wxApp
{
public:
    bool OnInit()
    {
        std::cout << "Hello" << std::endl;
        return true;
    }
};


IMPLEMENT_APP(App)
