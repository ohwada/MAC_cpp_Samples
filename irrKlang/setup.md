setup - irrKlang
===============

setup irrKlang for MAC <br/>

### download irrKlang  <br/>
https://www.ambiera.com/irrklang/downloads.html <br/>

latest version <br/>
irrKlang-64bit-1.6.0.zip <br/>

list of directories and files as below <br/>
- bin
- changes.txt
- doc
- examples
- examples.net
- include
- lib
- media
- plugins
- readme.txt

### copy files 
% sudo mkdir /usr/local/opt/irrklang
% sudo cp include/* /usr/local/opt/irrklang/includ/
% sudo cp  bin/macosx-gcc/*.dylib /usr/local/opt/irrklang/lib

### create a symbolic link

display following error when run app <br/>
dyld: Library not loaded: /usr/local/lib/libirrklang.dylib <br/>

% sudo ln -s /usr/local/opt/irrklang/lib/libirrklang.dylib /usr/local/lib/libirrklang.dylib <br/>


###  allow to use libirrklang.dylib

display following error when run app <br/>
> libirrklang.dylib: code signature in (/usr/local/lib/libirrklang.dylib) not valid for use in process using Library Validation: library load disallowed by system policy <br/>

and show dialog <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/irrKlang/screenshots/screenshot_libirrlang_warning.png" width="300" /><br/>

You can allow with system settibgs <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/irrKlang/screenshots/screenshot_libirrlang_security_setting.png" width="300" /><br/>

show dialog when run app again <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/irrKlang/screenshots/screenshot_libirrlang_confirm.png" width="300" /><br/>

###  setup for pkg-config
% sudo cp pkgconfig/irrklang.pc /usr/local/opt/irrklang/pkgconfig
% sudo ln -s /usr/local/opt/irrklang/pkgconfig/irrklang.pc /usr/local/lib/pkgconfig/irrklang.pc <br/>

check for pkg-config <br/>
% pkg-config --cflags --libs irrklang <br/>
display as below <br/>
-I/usr/local/opt/irrklang/include -L/usr/local/opt/irrklang/lib -lirrklang


###  setup for mp3
copy ikpMP3.dylib to same directory as the executable file <br/>

allow to use ikpMP3.dylib <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/irrKlang/screenshots/screenshot_ikpmp3_security_setting.png" width="300" /><br/>

### Reference <br/>
- https://www.ambiera.com/irrklang/
- https://forums.developer.apple.com/thread/128380
- https://support.apple.com/ja-jp/guide/mac-help/mh40617/10.15/mac/10.15
- https://ambiera.com/forum.php?t=847
