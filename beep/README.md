beep
===============

OpenAL Beep Sample <br/>
play beep sound  <br/>



###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>


## play_Beep.cpp <br/>
play beep sound with Beep class <br/>

### build sample code
% g++ play_beep.cpp Beep.cpp -o beep  -framework OpenAL  <br/>

### run sample code 
Usage: ./beep [freq] [duration] <br/>


## play_piano.cpp <br/>
// Keyboard Piano with beep <br/>

### build sample code
% g++ play_piano.cpp Beep.cpp keyboard.c -o piano  -framework OpenAL  <br/> 

### run sample code 
./piano <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/beep/result/screenshot_piano.png" width="300" /><br/>

## play_flog_song.cpp <br/>
play "Flog Song"  with beep <br/>
"Flog Song" is Japanese popular kid song <br/>
- https://youtu.be/H18SYpZShmQ <br/>

### build sample code 
% g++ play_flog_song.cpp flog_song.cpp -o flog    -std=c++11 -framework OpenAL <br/>


### Reference <br/>
- http://openal.org/

