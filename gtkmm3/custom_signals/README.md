gtkmm3: custom_signals
===============


### overview
Creating your own signals
Now that you've seen signals and signal handlers in gtkmm, you might like to use the same technique to allow interaction between your own classes.   
That's actually very simple by using the libsigc++ library directly.  

This isn't purely a gtkmm or GUI issue. gtkmm uses libsigc++ to implement its proxy wrappers for the GTK+ signal system, but for new, non-GTK+ signals, you can create pure C++ signals, using the sigc::signal<> template.


### samplrs
- server.cc
- client.cc

Build and Run:
% make signals
% bin/signals
> Before Server::do_something()
> Client::on_server_something() called with these parameters: 0, 5
> After Server::do_something()
