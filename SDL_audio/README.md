SDL_audio
===============

SDL Audio Sample <br/>
play audio file <br/>
SDL( Simple DirectMedia Layer ) is a cross-platform development library <br/>
designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware <br/>


## install SDL
% brew install sdl2 <br/>
% brew install sdl2_audio <br/>
https://formulae.brew.sh/formula/sdl2 <br/>

## play_beep.cpp
play beep sound <br/>

% g++ play_beep.cpp `pkg-config --cflags --libs sdl2` <br/>

## play_wav_loop.cpp
play wav file  in endless loop

% g++ play_wav_loop.cpp `pkg-config --cflags --libs sdl2` <br/>

## play_music_file.cpp
play music file <br/>

% g++ play_music_file.cpp -o play  `pkg-config --cflags --libs sdl2_mixer` <br/>


### Reference <br/>
- https://www.libsdl.org

