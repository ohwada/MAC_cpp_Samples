gtkmm3: plugs_sockets
===============

### overview
 Plugs and Sockets.  
gtkmm allows You to do this with the Gtk::Socket and Gtk::Plug classes.   
It is not anticipated that very many applications will need this functionality, but in the rare case that you need to display a widget that is running in a completely different process, these classes can be very helpful.

The communication between a Socket and a Plug follows the XEmbed protocol.   
This protocol has also been implemented in other toolkits (e.g. Qt), which allows the same level of integration when embedding a Qt widget in GTK+ or vice versa.

### samplrs
- plug.cc
- socket.cc

###  TODO
> fatal error: 'gtkmm/plug.h' file not found
> fatal error: 'gtkmm/socket.h' file not found

