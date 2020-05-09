fdk_aac
===============

fdk_aac Sample <br/>

play aac  <br/>
Advanced Audio Coding (AAC) <br/>
https://sourceforge.net/projects/opencore-amr/  <br/>

## install fdk-aac
% brew install fdk-aac <br/>
https://formulae.brew.sh/formula/fdk-aac <br/>

## conv_wav.cpp
convert aac to wav <br/>

### build sample code 
% g++ cov_wav.cpp fdkaac_dec.cpp wavwriter.c parse_filename.cpp -o conv `pkg-config --cflags --libs fdk-aac`  <br/>

### run sample code 
Usage: ./conv \< aacFile \> <br/> 
ex) <br/>
%  ./conv ./media/hello.aac <br/> 

saved :  hello.aac.wav <br/>


## play_aac.cpp <br/>
play aac file with OpenAL <br/>

### build sample code 
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

% g++ play_aac.cpp AacReader.cpp -o play -framework OpenAL `pkg-config --cflags --libs fdk-aac` <br/>

### run sample code 
Usage: ./play \< mp3File \> <br/>
ex)
% ./play ./media/hello.aac <br/>



## encode_from_aac.cpp
encode from aac <br/>

### build sample code 
% g++  encode_from_aac.cpp AacEncoder.cpp  wav_header.c parse_filename.cpp  -o encode `pkg-config --cflags --libs fdk-aac`  <br/> 


### run sample code 
Usage: ./encode \< wavFile \> <br/> 
ex) <br/>
%  ./encode ./media/song.wav <br/> 

saved :  song.wav.aac <br/>


### Reference <br/>
- https://sourceforge.net/projects/opencore-amr/
- https://github.com/akanchi/aac-example


