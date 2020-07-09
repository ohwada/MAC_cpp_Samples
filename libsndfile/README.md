libsndfile
===============

libsndfile sample <br/>

play audio file <br/>


Libsndfile is a C library for reading and writing files containing sampled sound <br/>
http://www.mega-nerd.com/libsndfile/ <br/>

###  install libsndfile
% brew install libsndfile <br/>
https://formulae.brew.sh/formula/libsndfile <br/>

###  requires
- macOS OpenAL.framework <br/>
https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/CoreAudioFrameworks/CoreAudioFrameworks.html <br/>
- cairo <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/cairo <br/>
- fftw <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/fftw

### list_formats.c
print list of suported formats

build code <br/>
% gcc src/list_formats.c -o list `pkg-config --cflags --libs  sndfile` <br/>

run code  <br/>
% ./list <br/>

### make_sine.c
make sin wave to wav file <br/>

build code <br/>
% gcc src/make_sine.c -o make `pkg-config --cflags --libs  sndfile` <br/>

run code  <br/>
Usage ./make \< left freq \> [ right freq] <br/>
ex) <br/>
% ./make 344 466 <br/>

display as below <br/>
created: sine_344_400.wav <br/>

### sndfile-to-text.c
convert audio fitl to text file <br/>

build code <br/>
% g++ src/sndfile-to-text.cpp src/parse_filename.cpp -o to_text `pkg-config --cflags --libs  sndfile` <br/>

run code  <br/>
Usage : to_tex \< input file \> t [--full-precision] <br/>
ex)
% ./to_text result/sine_344_466.wav <br/>

display as below <br/>
converted: sine_344_466.wav.txt <br/>

### generate-chirp.c
create a sound file containing a swept sine wave <br/>

build code <br/>
% gcc src/generate-chirp.c src/common.c -o chirp `pkg-config --cflags --libs sndfile` 

run code  <br/>
Usage : chirp  [options] \< sample rate \> \< length in seconds \> \< sound file \> <br/>
ex)
% ./ chirp <br/>

display as below <br/>
samplerate: 44100 <br/>
seconds: 2.000000 <br/>
Start frequency :    100.0 Hz (0.014248 rad/sec) <br/>
End   frequency :   1000.0 Hz (0.142472 rad/sec) <br/>
created: chirp_100_1000_44100_2.wav <br/>

### mix-to-mono.cpp
convert a multi-channel input file to a mono output file, 

build code <br/>
% g++ src/mix-to-mono.cpp  src/common.c src/parse_filename.cpp  -o mono `pkg-config --cflags --libs sndfile` <br/>

run code <br/>
Usage : mono \< input file \> [output file]  <br/>
ex) <br/>
% ./mono result/sine_344_466.wav <br/>

display as below <br/>
created: sine_344_466_mono.wav <br/>

### spectrogram.cpp
generate a spectrogram as a PNG file from a given sound file. <br/>

build code <br/>
% g++ src/spectrogram.cpp  src/spectrum.c src/window.c src/common.c  src/parse_filename.cpp -o spectrogram `pkg-config --cflags --libs sndfile` `pkg-config --cflags --libs fftw3` `pkg-config --cflags --libs cairo`

run code <br/>
Usage; <br/>
spectrogram [options] \< sound file \> [img width] [img height] [png name] <br/>
EX) <br/>
% ./ spectrogram result/chirp_200_22050_44100_2.wav <br/>

display as below <br/>
created: spectrogram_chirp_200_22050_44100_2.png <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libsndfile/result/spectrogram_chirp_200_22050_44100_2.png" width="300" /><br/>

### play_file_with_openal.cpp
play_file_with_OpenAL <br/>

build code <br/>
% g++ src/play_file_with_openal.cpp -o play -framework OpenAL `pkg-config --cflags --libs  sndfile` <br/>

run code  <br/>
Usage: ./play \< audioFile \> <br/>
ex) <br/>
%  ./play media/church-chime-daniel_simon.wav <br/>

display as below <br/>
channels: 2 <br/>
samplerate:  44100 <br/>
frames:  2874795 <br/>


### Reference <br/>
- https://github.com/erikd/libsndfile/

