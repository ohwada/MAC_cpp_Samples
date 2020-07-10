flac
===============

flac Sample <br/>

play flac <br/>

Free Lossless Audio Codec <br/>
https://xiph.org/flac/ <br/>

### install flac
% brew  install flac <br/>
https://formulae.brew.sh/formula/flac <br/>

## conv_wav.cpp 
convert flac to wav <br/>

### build sample code 
% g++ conv_wav.cpp FlacReader.cpp wav_header.c parse_filename.cpp -o conv  `pkg-config --cflags --libs flac` <br/>

### run sample code 
Usage: ./conv \< flacFile \> <br/>
ex) <br/>
%  ./conv ./media/BIS1447-002-flac_16.flac <br/>

create file BIS1447-002-flac_16.flac.wav <br/>


## play_flac.cpp <br/>
play flac file with OpenAL<br/>

### build sample code 
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

% g++ play_flac.cpp FlacReader.cpp -o play -framework OpenAL `pkg-config --cflags --libs flac` <br/>

### run sample code 
Usage: ./play \< flacFile \> <br/>
ex)
% ./play ./media/BIS1536-001-flac_16.flac <br/>

## encode_flac_from_wav.cpp
encode flac from wav <br/>

### build sample code 
% g++ encode_from_wav.cpp wav_header.c parse_filename.cpp -o encode `pkg-config --cflags --libs flac++` <br/>

### run sample code 
Usage: ./encode \< wavFile \> <br/>
ex) <br/>
% ./encode ./media/church-chime-daniel_simon.wav  <br/>

saved: church-chime-daniel_simon.wav.flac <br/>


### Reference <br/>
- https://xiph.org/flac/ <br/>
-  https://github.com/xiph/flac/tree/master/examples <br/>

