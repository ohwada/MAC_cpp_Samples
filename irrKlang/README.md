irrKlang
===============

irrKlange Sample <br/>

play audio file <br/>

irrKlang is a cross platform sound library for C++, C# and all .NET languages. <br/>
https://www.ambiera.com/irrklang/ <br/>


###  setup irrKlang <br/>
(1) download irrKlang 1.6 (64 bit) <br/>
https://www.ambiera.com/irrklang/downloads.html <br/>
(2) unzip <br/>
(3) copy liblary to system area <br/>
% cp ./bin/macosx-gcc ./lib/libirrklang.dylib /usr/local/lib/ <br/>
(4) unlock Security check <br/>
https://support.apple.com/ja-jp/guide/mac-help/mh40617/10.15/mac/10.15 <br/>


### build sample code
% g++ sample.cpp -I./include -lirrklang

## HelloWorld.cpp <br/>
This example will show how to play sounds using irrKlang. <br/>
It will play a looped background music and a sound every
time the user presses a key. <br/>
Press any key to play some sound,  <br/>
press 'q' to quit.  <br/>

% g++ HelloWorld.cpp -I./include -lirrklang

## 3DSound.cpp <br/>
This example will show how to play sounds in 3D space using irrKlang. <br/>
An mp3 file file be played in 3D space and moved around the user  <br/>
and a sound will be played at a random 3D position every time 
the user presses a key. <br/>

require MP3 plugin <br/>
copy ikpMP3.dylib to same directory as the executable file <br/>
https://ambiera.com/forum.php?t=847<br/>

% g++ 3DSound.cpp -I./include -lirrklang

## MemoryPlayback.cpp <br/>
This example will show how to play sounds directly from memory using irrKlang. <br/>
This is useful for embedding sounds directly in executables as well for making irrKlang work together with different APIs like advanced decoders or middleware such as Shockwave. <br/>

## OverrideFileAccess.cpp <br/>
This example will show how to override file access with irrKlang. <br/>
This is useful if you want to read sounds from other sources than
just files,  <br/>
for example from custom internet streams or 
an own encypted archive format. <br/>

### Reference <br/>
- https://www.ambiera.com/irrklang/

