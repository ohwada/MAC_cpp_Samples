libvorbis examples
===============

libvorbis Sample <br/>

the files with this directory <br/>
was downloaded from the following <br/>
https://github.com/xiph/vorbis/tree/master/examples <br/>

### samples
- vorbisfile_example.c <br/>
simple example decoder using vorbisfile <br/>

-decoder_example.c <br/>
 simple example decoder <br/>

- encoder_example.c <br/>
simple example encoder <br/>

- chaining_example.c <br/>
illustrate simple use of chained bitstream and vorbisfile.a <br/>

- seeking_example.c <br/>
illustrate seeking, and test it too <br/>


### Buid and Run
% gcc vorbisfile_example.c -o vorbisfile `pkg-config --cflags --libs vorbis`  -lvorbisfile  <br/>

% cat media/ImpactModerato.ogg | ./vorbisfile > ImpactModerato.pcm <br/>
> Bitstream is 2 channel, 44100Hz

convert pcm to wav <br/>
Require: sox <br/>
https://formulae.brew.sh/formula/sox <br/>

% sox -t raw -e signed-integer -c 2 -b 16 -r 44100  ImpactModerato.pcm -t wav  ImpactModerato.wav <br/>

