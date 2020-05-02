wav
===============

wav Sample <br/>
play wav file  <br/>


###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>

##  create_tone-wav.cpp <br/>
create tone wav file <br/>

### build sample code 
% g++ create_tone_wav.cpp wav_header.c  -o tone <br/>

### run sample code 
Usage: ./tone [freq] [duration]  <br/>
ex) ./tone 440 1 <br/>

create tone_440_1.wav <br/>

##  create_wav_flog_song.cpp <br/>
create wav file of "Flog Sng" <br/>
"Flog Song" is Japanese popular kid song <br/>
https://youtu.be/H18SYpZShmQ <br/>

### build sample code 
% g++ create_wav_flog_song.cpp flog_song.cpp wav_header.c  -o flog -std=c++11 <br/>

### run sample code 
% ./flog  <br/>

ctreate flog_song.wav  <br/>

## play_wav_with_openal.cpp <br/>
play wav file with OpenAL <br/>

### build sample code 
% g++ play_wav_with_openal.cpp wav_header.c -o play -framework OpenAL


### run sample code 
Usage: ./play \ <wavFile \> <br/> 
ex) <br/>
% ./play ./media/church-chime-daniel_simon.wav <br/>

## play_wav_with_pulseaudio.cpp <br/>
play wav file with PulseAudio <br/>

### build sample code 
reqire PulseAudio <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/PulseAudio <br/>

% g++ play_wav_with_pulseaudio.cpp wav_header.c -o pa `pkg-config --cflags --libs libpulse` -lpulse-simple

### run sample code 
Usage: ./pa \ <wavFile \> <br/> 
ex) <br/>
% ./pa ./media/church-chime-daniel_simon.wav <br/>

### Reference <br/>
- http://openal.org/
- http://www-fps.nifs.ac.jp/ito/memo/openal02.html

