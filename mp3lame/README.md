mp3lame
===============

mp3lame Sample <br/>
encode mp3 <br/>

MPEG Audio Layer III (MP3) encoder <br/>
https://lame.sourceforge.io/ <br/>


### install libmp3lame
% brew install lame <br/>
https://formulae.brew.sh/formula/lame <br/>

## encode_from_wav.cpp
encode mp3 from wav <br/>

### build sample code 
% g++ encode_from_wav.cpp wav_header.c parse_filename.cpp -o encode   -I/usr/local/Cellar/lame/3.100/include/ -L/usr/local/Cellar/lame/3.100/lib -lmp3lame

### run sample code 
Usage: ./encode \ <wavFile \> <br/>
ex) <br/>
%  ./encode ./media/church-chime-daniel_simon.wav <br/>

saved: church-chime-daniel_simon.wav.mp3 <br/>

### Reference <br/>
- https://lame.sourceforge.io/
- https://stackoverflow.com/questions/2495420/is-there-any-lame-c-wrapper-simplifier-working-on-linux-mac-and-win-from-pure

