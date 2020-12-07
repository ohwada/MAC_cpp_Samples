tcp - glib
===============

glib / gio sample <br/>
TCP Client and Server using GLib GSocket <br/>

GSocket: <br/>
Low-level socket object <br/>
https://developer.gnome.org/gio//2.34/GSocket.html <br/>

## sample code
- echo_client.c <br/>
 TCP Echo Client <br/>
- echo_server.c <br/>
TCP Echo Server <br/>

build sample code<br/>
% gcc echo_server.c `pkg-config --cflags --libs gio-2.0` -o server <br/>

run sample code <br/>
% ./server <br/>

display as below <br/>
> Waiting for client port: 1500 <br/>

### Reference <br/>
- https://developer.gnome.org/glib/stable/
- https://developer.gnome.org/gio/stable/
- https://developer.gnome.org/gio//2.34/GSocket.html <br/>


