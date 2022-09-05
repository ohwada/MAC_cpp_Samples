gtkmm3: menu
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gtkmm3/screenshots/menu.png" width="300" /> 

### overview
Menus and Toolbars  
There are specific APIs for Menus and toolbars, but you should usually deal with them together, using the UIManager to define Actions which You can then arrange in menu and toolbars.   
In this way You can handle activation of the action instead of responding to the menu and toolbar items separately.   
And You can enable or disable both the menu and toolbar item via the action.

### samplrs
- examplewindow.cc

Build and Run:
% make menu
% bin/menu
