gio - glib
===============

glib / gio sample <br/>
- read and write file <br/>
- HTTP Client and Server <br/>

GIO (Gnome Input/Output) : <br/>
 a C library, designed to present programmers with a modern and usable interface to a virtual file system. <br/>
GIO is part of GLib <br/>

## sample code
- read_write_text_file.c <br/>
read and write text file like copying file <br/>
 
build sample code<br/>
% gcc gio/read_write_text_file.c `pkg-config --cflags --libs gio-2.0` <br/>

run sample code <br/>
Usage: ./a.out [input file] [output file] [overwrite]  <br/>

display as below <br/>
> write to : sample_out.txt <br/>

### tcp
TCP Client and Server using GLib GSocket <br/>

### http
HTTP Client and Server using GLib GSocket <br/>


### Reference <br/>
- https://developer.gnome.org/glib/stable/
- https://developer.gnome.org/gio/stable/

