libmad
===============

libmad Sample <br/>

convert mp3 to wav <br/>
MPEG Audio Decoder <br/>
https://www.underbit.com/products/mad/

## install libmad
% brew  install libmad
https://formulae.brew.sh/formula/mad

## minimad.c
this is perhaps the simplest example use of the MAD high-level API. <br/>
stdin : mp3 file <br/>
stdout : decoded pcm data <br/>

### build sample code 
% gcc minimad.c -o test `pkg-config --cflags --libs mad` <br/>

### run sample code 
ex) <br/>
% ./test < ./media/bell.mp3  <br/>

## conv_wav
convert mp3 to wav <br/>

### build sample code 
g++ ./conv_wav/*.cpp -fdeclspec -o conv `pkg-config --cflags --libs mad`

### run sample code 
Usage: ./conv \< mp3File \> <br/> 
ex) <br/>
./conv ./media/Mozart-EineKleine-1st.mp3 <br/> 

### result <br/>
create Mozart-EineKleine-1st.mp3.wav <br/>

### Reference <br/>
- https://www.underbit.com/products/mad/
- https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM
