irrKlang
===============

irrKlange Sample <br/>

irrKlang is a cross platform sound library for C++, C# and all .NET languages. <br/>
https://www.ambiera.com/irrklang/ <br/>


###  setup irrKlang <br/>
https://github.com/ohwada/MAC_cpp_Samples/blob/master/irrKlang/setup.md  <br/>


## play_file.cpp <br/>
play audio file

if You want to play mp3 <br/>
copy ikpMP3.dylib to same directory as the executable file <br/>

### build sample code
% g++ play_file.cpp -o play `pkg-config --cflags --libs irrklang` <br/>

### run sample code
Usage: ./play \< audioFile \>  <br/>
ex) <br/>
% ./play ./media/bell.wav <br/>

display as below  <br/>
irrKlang sound library version 1.6.0 <br/>
Loaded plugin: ikpMP3.dylib <br/>
Using CoreAudio driver <br/>
press 'q' to quit <br/>

## HelloWorld.cpp <br/>
This example will show how to play sounds using irrKlang. <br/>

build sample code<br/>
% g++ examples/HelloWorld.cpp -o hello  `pkg-config --cflags --libs irrklang` <br/>


## 3DSound.cpp <br/>
This example will show how to play sounds in 3D space using irrKlang. <br/>

build sample code<br/>
% g++ examples/3DSound.cpp  -o 3dsound  `pkg-config --cflags --libs irrklang`

## MemoryPlayback.cpp <br/>
This example will show how to play sounds directly from memory using irrKlang. <br/>

build sample code<br/>
% g++ examples/MemoryPlayback.cpp  -o memory  `pkg-config --cflags --libs irrklang ` <br/>


## OverrideFileAccess.cpp <br/>
this example will show how to override file access with irrKlang. <br/>

build sample code<br/>
% g++ examples/OverrideFileAccess.cpp  -o override  `pkg-config --cflags --libs irrklang ` <br/>

## Effects.cpp <br/>
this example will show how to use sound effects such as echo, reverb and distortion.
this program does not work on MAC

build sample code<br/>
% g++ examples/Effects.cpp  -o effects  `pkg-config --cflags --libs irrklang ` <br/>

display as below, when run code <br/>
this device or sound does not support sound effects. <br/>

## Recording.cpp <br/>
this example will show how to record and play back audio. 
this program does not work on MAC

build sample code<br/>
% g++ examples/Recording.cpp  -o recording  `pkg-config --cflags --libs irrklang` <br/>

display as below, when run code <br/>
Could not create audio engine or audio recoder <br/>

### Reference <br/>
- https://www.ambiera.com/irrklang/
- https://ambiera.com/forum.php?t=847<br/>

