libvorbis src
===============

libvorbis Sample <br/>

### samples
- conv_ogg_to_wav.cpp <br/>
- conv_ogg_to_wav_list.cpp  <br/>
- conv_wav_to_ogg.cpp <br/>
- play_ogg.cpp <br/>


### Buid and Run
conv_ogg_to_wav.cpp: <br/>
(1) % make decode <br/>
or <br/>
(2) % g++ conv_ogg_to_wav.cpp -o decode `pkg-config --cflags --libs vorbis` `pkg-config --cflags --libs ogg` <br/>
(3) % ./decode media/ImpactModerato.ogg
> save to: ImpactModerato.ogg.wav

play ogg.cpp : <br/>
Require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

