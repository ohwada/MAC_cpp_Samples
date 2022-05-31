SDL2_mixer
===============

SDL2 mixer Sample <br/>
play music file <br/>

## install SDL2_mixer
% brew install sdl2_mixer <br/>
https://formulae.brew.sh/formula/sdl2_mixer <br/>

## play_music_file.c
play music file <br/>

build file <br/>
% gcc play_music_file.c -o play  `pkg-config --cflags --libs sdl2_mixer`  <br/>
or <br/>
% gcc play_music_file.c -lSDL2_mixer -lSDL2 -o play <br/>

run <br/>
%  ./play media/J.S.Bach-Menuet-Piano.mp3

### Reference <br/>
- https://www.libsdl.org

