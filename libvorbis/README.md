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
> /usr/local/Cellar/libvorbis/1.3.7/include <br/>

% brew install libogg <br/>
https://formulae.brew.sh/formula/libogg <br/>
% pkg-config --cflags --libs ogg  br/>
> /usr/local/Cellar/libogg/1.3.5/include <br/>

## exsamples
- vorbisfile_example.c <br/>
-decoder_example.c <br/>
- encoder_example.c <br/>
- chaining_example.c <br/>

### src
- conv_ogg_to_wav.cpp <br/>
- conv_ogg_to_wav_list.cpp  <br/>
- conv_wav_to_ogg.cpp <br/>
- play_ogg.cpp <br/>


### Reference <br/>
- https://xiph.org/vorbis/
- https://www.xiph.org/ogg/
- https://github.com/xiph/vorbis

