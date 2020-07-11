sfml audio
===============

sfml sample <br/>
play audio fie <br/>


## install sfml
% brew install sfml <br/>
https://formulae.brew.sh/formula/sfml <br/>

## setup
modify sfml-audio.pc <br/>
because  display the following error <br/>
Package openal was not found in the pkg-config search path. <br/>

remove openal in <br/>
/usr/local/Cellar/sfml/2.5.1/lib/pkgconfig/sfml-audio.pc <br/>
or <br/>
% sudo cp pkgconfig/sfml-audio.pc /usr/local/Cellar/sfml/2.5.1/lib/pkgconfig/ <br/>

## play_tone.cpp
play sin wave tone <br/>

build code  <br/>
% g++ src/play_tone.cpp -o tone  `pkg-config --cflags --libs sfml-audio`  <br/>

run code  <br/>
Usage: ./tone [freq] [duration]  <br/>
ex) 
% ./tone 440 1 <br/>

## play_sound.cpp
play sound file <br/>

### build code 
% g++ src/play_sound.cpp -o sound `pkg-config --cflags --libs sfml-audio`  <br/>

### run code 
Usage: sound \< soundFile \> <br/>
ex) <br/>
% ./sound media/Temple_Bell_Huge.wav <br/>

display as below <br/>
playtime: 5.32172 sec <br/>

## play_music.cpp
play music file <br/>

### build code 
% g++ src/play_music.cpp -o music `pkg-config --cflags --libs sfml-audio`  <br/>

### run code 
Usage: music \< musicFile \> <br/>
ex) <br/>
% ./music media/m-art_madoromi.ogg <br/>

display as below <br/>
playtime: 78.1556 sec <br/>
 (  70 sec) <br/>

### Reference <br/>
- https://riptutorial.com/sfml
- https://www.sfml-dev.org/tutorials/2.5/audio-sounds.php


