http - glib
===============

glib / gio sample <br/>
HTTP Client and Server using GLib GSocket <br/>

## sample code
- http_client.c <br/>
 HTTP Client <br/>
- http_server.c <br/>
HTTP Server <br/>

build sample code<br/>
% gcc http_server.c `pkg-config --cflags --libs gio-2.0` -o server <br/>

run sample code <br/>
Usage: ./server  [port] <br/>
% ./server <br/>

display as below <br/>
> Waiting for client port: 8080 <br/>

access localhost:8080 by WEB Brawser <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/glib/screenshot/chrome_http_server.png" width="300" />


### Reference <br/>
- https://developer.gnome.org/glib/stable/
- https://developer.gnome.org/gio/stable/
- https://developer.gnome.org/gio//2.34/GSocket.html <br/>


