gtkmm3: pushubutton
===============

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/gtkmm3/screenshots/pushubutton.png" width="300" /> 

### overview
Buttons
gtkmm provides four basic types of buttons:

(1) Push-Buttons  
Gtk::Button. Standard buttons, usually marked with a label or picture. Pushing one triggers an action. See the Button section.

(2) Toggle buttons  
Gtk::ToggleButton. Unlike a normal Button, which springs back up, a ToggleButton stays down until you press it again. It might be useful as an on/off switch. See the ToggleButton section.

(3) Checkboxes  
Gtk::CheckButton. These act like ToggleButtons, but show their state in small squares, with their label at the side. They should be used in most situations which require an on/off setting. See the CheckBox section.

(4) Radio buttons  
Gtk::RadioButton. Named after the station selectors on old car radios, these buttons are used in groups for options which are mutually exclusive. Pressing one causes all the others in its group to turn off. They are similar to CheckBoxes (a small widget with a label at the side), but usually look different. See the RadioButton section.

This example creates a button with a picture and a label.

### samplrs
- buttons.cc

Build and Run:
% make buttons
% bin/buttons
