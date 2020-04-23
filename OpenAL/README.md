OpenAL
===============

OpenAL Sample <br/>
play audio file  <br/>
wav, ogg, mp3  <br/>
 OpenAL is a cross-platform 3D audio API appropriate  <br/>
http://openal.org/ <br/>


###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>

- alure <br/>
% brew install alure <br/>
https://formulae.brew.sh/formula/allure <br/>
- libmad <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmad <br/>
- libvorbis <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libvorbis <br/>


## test_tone.cpp <br/>
play 440 Hz tone for 3 seconds <br/>

### build sample code 
% g++ test_tone.cpp -o tone -framework OpenAL <br/>

### run sample code 
% ./tone  <br/>

## test_wav.cpp <br/>
play wav file <br/>

### build sample code 
require alure <br/>
% brew install alure <br/>

% g++ play_wav.cpp -o wav -framework OpenAL -I/usr/local/Cellar/alure/1.2_1/include/  -L/usr/local/Cellar/alure/1.2_1/lib/ -lalure-static <br/>

display following warning when build <br/>
but don't mind <br/>
warning: 'alcOpenDevice' is deprecated: first deprecated in
      macOS 10.15 <br/>

Note: <br/>
macOS Catalina 10.15 Release Notes <br/>
The OpenAL framework is deprecated <br/>
https://developer.apple.com/documentation/macos_release_notes/macos_catalina_10_15_release_notes <br/>


### run sample code 
Usage: ./wav \ <wavFile \> <br/> 
ex) <br/>
% ./wav ./media/Japanese_Temple_Bell_Small.wav <br/>

## play_ogg.cpp <br/>
play ogg file <br/>

### build sample code 
require libvorbis <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libvorbis <br/>

% gcc play_ogg.c -o ogg -framework OpenAL  `pkg-config --cflags --libs vorbis` -lvorbisfile

### run sample code 
Usage: ./ogg \ <oggFile \> <br/> 
ex) <br/>
% ./ogg ./media/Example.ogg <br/>


## play_mp3.cpp <br/>
play mp3 file <br/>

### build sample code 
require libmad <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmad <br/>

% gcc play_mp3.c -o mp3 -framework OpenAL `pkg-config --cflags --libs mad` <br/>

### run sample code 
Usage: ./mp3 \< mp3File \> <br/>
ex)
% ./mp3 ./media/Mozart-EineKleine-1st.mp3 <br/>


### Reference <br/>
- http://openal.org/
- https://kcat.strangesoft.net/alure.html

