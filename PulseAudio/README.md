PulseAudio
===============

PulseAudio Sample <br/>
play audio file <br/>

PulseAudio is a sound system for POSIX OSes <br/>
https://wiki.freedesktop.org/www/Software/PulseAudio/ <br/>

### install PulseAudio
% brew install pulseaudio
https://formulae.brew.sh/formula/pulseaudio

##  play_tone.cpp <br/>
play tone <br/>

### build sample code 
% g++ play_tone.cpp -o tone `pkg-config --cflags --libs libpulse`  -lpulse-simple <br/>

### run sample code 
% ./tone  <br/>

## play_wav <br/>
play wav file <br/>

### build sample code 
% g++ ./play_wav/*.cpp -o play `pkg-config --cflags --libs libpulse`

### run sample code 
Usage: ./play \ <wavFile \> <br/> 
ex) <br/>
% ./play ./media/church-chime-daniel_simon.wav <br/>

## play mp3 file
see libmad <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libmad <br/>

### Reference <br/>
- https://wiki.freedesktop.org/www/Software/PulseAudio/
- http://ysflight.in.coocan.jp/programming/audio/pulseAudioSample/j.html

