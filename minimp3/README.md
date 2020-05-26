minimp3
===============

minimp3 Sample <br/>
play mp3 <br/>

Minimalistic MP3 decoder single header library <br/>

## conv_wav.cpp
convert mp3 to wav <br/>

### build sample code 
% g++ conv_wav.cpp wav_header.c parse_filename.cpp  -o conv <br/>

### run sample code 
Usage: ./conv \< mp3File \> <br/> 
ex) <br/>
%  ./conv ./media/Mozart-EineKleine-1st.mp3 <br/> 

saved : Mozart-EineKleine-1st.mp3.wav <br/>

## play_mp3_with_openal.cpp
play mp3 file with OpenAL <br/>

### build sample code
require OpenAL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenAL <br/>

g++ play_mp3_with_openal.cpp -o play -std=c++11  -framework OpenAL 

### run sample code 
Usage: ./play \< mp3File \> <br/> 
ex) <br/>
%  ./play ./media/Mozart-EineKleine-1st.mp3 <br/> 

## play_mp3_with_sdl.cpp
play mp3 file with SDL <br/>

### build sample code
require SDL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/SDL

% g++ play_mp3.cpp  ./src/audio_sdl.c  ./src/decode.c  -o sdl -std=c++11  `pkg-config --cflags --libs sdl2` <br/>

### run sample code 
Usage: ./sdl \< mp3File \> <br/> 
ex) <br/>
%  ./sdl ./media/Mozart-EineKleine-1st.mp3 <br/> 


## player.cpp
mp3 player with OpenGL and SDL <br/>

### requires  
- macOS  OpenGL framework <br/>
https://developer.apple.com/library/archive/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_intro/opengl_intro.html <br/>
- glfw <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/OpenGL-GLFW
- SDL <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/SDL


### build sample code 
% g++  ./player/player.cpp ./player/*.c -o mp3player --std=c++11  -framework OpenGL `pkg-config --cflags --libs glfw3` `pkg-config --cflags --libs sdl2`  


### run sample code 
% ./mp3player ./media/*.mp3 <br/>
play music automatically <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/minimp3/result/screenshot_player.png" width="300" /><br/>

### Reference <br/>
- https://github.com/lieff/minimp3


