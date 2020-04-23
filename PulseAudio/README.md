PulseAudio
===============

PulseAudio Sample <br/>
play audio file <br/>
wav, mp3 <br/>

PulseAudio is a sound system for POSIX OSes <br/>
https://wiki.freedesktop.org/www/Software/PulseAudio/ <br/>

### install PulseAudio
% brew install pulseaudio
https://formulae.brew.sh/formula/pulseaudio

## test_beep.c <br/>
play beep <br/>

### build sample code 
% gcc test_beep.c -o beep `pkg-config --cflags --libs libpulse` <br/>

### run sample code 
% ./beep  <br/>

## play_wav <br/>
play wav file <br/>

### build sample code 
 g++ ./play_wav/*.cpp -o wav `pkg-config --cflags --libs libpulse`

### run sample code 
Usage: ./wav \ <wavFile \> <br/> 
ex) <br/>
% ./wav ./media/Japanese_Temple_Bell_Small.wav <br/>

## play_mp3.cpp <br/>
play mp3 file <br/>

### build sample code 
require libmad <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmad <br/>

% gcc play_mp3.c -o mp3 `pkg-config --cflags --libs libpulse` `pkg-config --cflags --libs mad` -lpulse-simple  <br/>

### run sample code 
Usage: ./mp3 \< mp3File \> <br/>
ex)
% ./mp3 ./media/Mozart-EineKleine-1st.mp3 <br/>

### Reference <br/>
- https://wiki.freedesktop.org/www/Software/PulseAudio/
- http://ysflight.in.coocan.jp/programming/audio/pulseAudioSample/j.html
- https://lauri.xn--vsandi-pxa.com/2013/12/implementing-mp3-player.en.html

