libvorbis
===============

libvorbis Sample <br/>

convert ogg to wav <br/>

Vorbis audio compression <br/>
https://xiph.org/vorbis/ <br/>


### install libvorbis and libogg
% brew install libvorbis <br/>
https://formulae.brew.sh/formula/libvorbis <br/>

% brew install libogg <br/>
https://formulae.brew.sh/formula/libogg <br/>

## decoder_example.c
Takes a vorbis bitstream from stdin  <br/>
and writes raw stereo PCM to stdout.  <br/>

### build sample code 
% gcc decoder_example.c -o decoder `pkg-config --cflags --libs vorbis``pkg-config --cflags --libs ogg`

### run sample code 
ex) <br/>
% ./decoder < ./media/Example.ogg  <br/>


## encoder_example.c
takes a stereo 16bit 44.1kHz WAV file from stdin <br/>
and encodes it into a Vorbis bitstream  <br/>

### build sample code 
% gcc encoder_example.c -o encoder `pkg-config --cflags --libs vorbis``pkg-config --cflags --libs ogg`  -lvorbisenc <br/>

### run sample code 
ex) <br/>
% ./encoder < ./media/Japanese_Temple_Bell_Small.wav


## conv_wav.cpp
convert ogg to wav <br/>

### build sample code 
% g++ conv_wav.cpp wav_header.c parse_filename.cpp -o conv `pkg-config --cflags --libs vorbis`  -lvorbisfile

### run sample code 
Usage: ./conv <oggFile> <br/> 
ex) <br/>
./conv ./media/m-art_Shine.ogg <br/> 

### result <br/>
create m-art_Shine.ogg.wav <br/>


### Reference <br/>
- https://xiph.org/vorbis/
- https://www.xiph.org/ogg/
- https://github.com/xiph/vorbis

