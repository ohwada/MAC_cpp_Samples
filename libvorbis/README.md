libvorbis
===============

libvorbis Sample <br/>

play ogg file <br/>

Vorbis audio compression <br/>
https://xiph.org/vorbis/ <br/>


### install libvorbis and libogg
% brew install libvorbis <br/>
https://formulae.brew.sh/formula/libvorbis <br/>

% brew install libogg <br/>
https://formulae.brew.sh/formula/libogg <br/>

## conv_wav.cpp
convert ogg file to wav file <br/>

### build sample code 
% g++ conv_wav.cpp OggReader.cpp wav_header.c parse_filename.cpp -o conv `pkg-config --cflags --libs vorbis`  -lvorbisfile

### run sample code 
Usage: ./conv <oggFile> <br/> 
ex) <br/>
%  ./conv ./media/m-art_Shine.ogg <br/> 

saved: m-art_Shine.ogg.wav <br/>

## play_ogg.cpp
play ogg file <br/>

### build sample code 
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

% g++ play_ogg.cpp OggReader.cpp -o play -framework OpenAL `pkg-config --cflags --libs vorbis` -lvorbisfile

### run sample code 
Usage: ./play \ <oggFile \> <br/> 
ex) <br/>
% ./play ./media/m-art_Shine.ogg <br/>

## encode_from_wav.cpp
encoder sample <br/>
encode ogg from wav <br/>
use libvorbisenc <br/>
https://xiph.org/vorbis/doc/vorbisenc/index.html  <br/>

### build sample code 
% g++ encode_from_wav.cpp wav_header.c parse_filename.cpp -o encode  `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`  -lvorbisenc

### run sample code 
Usage: ./encode \ <wavFile \> <br/>
ex) <br/>
%  ./encode ./media/church-chime-daniel_simon.wav <br/>

saved: church-chime-daniel_simon.wav.ogg

### Reference <br/>
- https://xiph.org/vorbis/
- https://www.xiph.org/ogg/
- https://github.com/xiph/vorbis

