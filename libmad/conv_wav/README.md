conv_wav - libmad
===============

libmad Sample <br/>
convert mp3 to wav <br/>

### require
libmad <br/>
https://www.underbit.com/products/mad/  <br/>

### build sample code 
g++ *.cpp -fdeclspec -o conv `pkg-config --cflags --libs mad`

### run sample code 
Usage: ./conv \< mp3File \> <br/> 

### Reference <br/>
- https://www.underbit.com/products/mad/
- https://www.codeproject.com/Articles/7667/DLL-To-Decode-MP3-To-WAV-PCM
