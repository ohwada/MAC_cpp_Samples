stb_vorbis
===============

sample code for stb_vorbis.c <br/>
Ogg Vorbis decoder <br/>
http://www.nothings.org/stb_vorbis/

## conv-wav.cpp
convert ogg file to wav file <br/>

build sample code <br/>
% g++ conv_wav.cpp wav_header.c parse_filename.cpp  include/stb_vorbis.c -o conv  -I./include 

run sample code <br/>
Usage: ./conv \< oggFile \> <br/> 
ex) <br/>
% ./conv media/sketch008.ogg <br/>

saved: sketch008.ogg.wav <br/>

### Reference <br/>
- http://www.nothings.org/stb_vorbis/
- https://github.com/nothings/stb
