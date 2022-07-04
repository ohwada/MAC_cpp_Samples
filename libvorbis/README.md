libvorbis
===============

libvorbis Sample <br/>
play ogg file <br/>

Vorbis audio compression <br/>
https://xiph.org/vorbis/ <br/>


### install libvorbis and libogg
% brew install libvorbis <br/>
https://formulae.brew.sh/formula/libvorbis <br/>
% pkg-config --cflags --libs vorbis br/>
> /usr/local/Cellar/libvorbis/1.3.7/include br/>

% brew install libogg <br/>
https://formulae.brew.sh/formula/libogg <br/>
% pkg-config --cflags --libs ogg  br/>
> /usr/local/Cellar/libogg/1.3.5/include br/>

## conv_wav_to_wav.cpp
convert ogg file to wav file <br/>

Build and Run  <br/>
% g++ conv_ogg_to_wav.cpp ogg_reader.cpp -o decode -std=c++11 `pkg-config --cflags --libs vorbis`  -lvorbisfile  <br/>
%  ./decode ./media/m-art_Shine.ogg <br/> 


## conv_wav_to_wav.cpp
convert wav file to ogg file <br/>

Build and Run  <br/>
% g++ conv_wav_to_ogg.cpp -o encode  `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg`  -lvorbisenc
%  ./encode ./media/church-chime-daniel_simon.wav <br/>


## play_ogg.cpp
play ogg file <br/>

Build and Run <br/>
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

% g++ play_ogg.cpp ogg_reader.cpp -o play -framework OpenAL `pkg-config --cflags --libs vorbis` -lvorbisfile <br/>
% ./play ./media/m-art_Shine.ogg <br/>


### Reference <br/>
- https://xiph.org/vorbis/
- https://www.xiph.org/ogg/
- https://github.com/xiph/vorbis

