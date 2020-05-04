libmad
===============

libmad Sample <br/>

play mp3  <br/>
MPEG Audio Decoder <br/>
https://www.underbit.com/products/mad/

## install libmad
% brew  install libmad <br/>
https://formulae.brew.sh/formula/mad <br/>

## conv_wav.cpp
convert mp3 to wav <br/>

### build sample code 
% g++ conv_wav.cpp  MP3Reader.cpp wav_header.c parse_filename.cpp -o conv `pkg-config --cflags --libs mad`

### run sample code 
Usage: ./conv \< mp3File \> <br/> 
ex) <br/>
%  ./conv ./media/Mozart-EineKleine-1st.mp3 <br/> 

create Mozart-EineKleine-1st.mp3.wav <br/>


## play_mp3_with_openal.cpp <br/>
play mp3 file with OpenAL <br/>

### build sample code 
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

% g++ play_mp3_with_openal.cpp MP3Reader.cpp -o play -framework OpenAL `pkg-config --cflags --libs mad` <br/>

### run sample code 
Usage: ./play \< mp3File \> <br/>
ex)
% ./play ./media/Mozart-EineKleine-1st.mp3 <br/>

## play_mp3_with_pulseaudio.cpp <br/>
play mp3 file with PulseAudio <br/>

### build sample code 
require PulseAudio <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/PulseAudio <br/>

% g++ g++ play_mp3_with_pulseaudio.cpp MP3Reader.cpp -o pa  `pkg-config --cflags --libs mad` `pkg-config --cflags --libs libpulse` -lpulse-simple <br/>

### run sample code 
Usage: ./pa \< mp3File \> <br/>
ex)
% ./pa ./media/Mozart-EineKleine-1st.mp3 <br/>

### Reference <br/>
- https://www.underbit.com/products/mad/
- https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM
