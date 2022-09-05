gtkmm3: range_widgets
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gtkmm3/screenshots/range.png" width="300" /> 

### overview
Range Widgets  
Gtk::Scale and Gtk::Scrollbar both inherit from Gtk::Range and share much functionality.   
They contain a "trough" and a "slider" (sometimes called a "thumbwheel" in other GUI environments).   
Dragging the slider with the pointer moves it within the trough, while clicking in the trough advances the slider towards the location of the click, either completely, or by a designated amount, depending on which mouse button is used. This should be familiar scrollbar behaviour.

As will be explained in the Adjustment section, all Range widgets are associated with a Adjustment object.   
To change the lower, upper, and current values used by the widget you need to use the methods of its Adjustment, which you can get with the get_adjustment() method.   
The Range widgets' default constructors create an Adjustment automatically, or You can specify an existing Adjustment, maybe to share it with another widget. See the Adjustments section for further details.

### samplrs
- examplewindow.cc

Build and Run:
% make range
% bin/range
