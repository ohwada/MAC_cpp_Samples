SDL
===============

SDL Sample <br/>
open SDL window and show image <br/>
SDL( Simple DirectMedia Layer ) is a cross-platform development library <br/>
designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware <br/>


## install SDL
% brew install sdl2 <br/>
% brew install sdl2_image <br/>
https://formulae.brew.sh/formula/sdl2 <br/>

## test_hello.c
display SDL window <br/>

% gcc test_hello.c -o hello `pkg-config --cflags --libs sdl2`

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/SDL/result/screenshot_hello.png" width="300" /><br/>

## test_drawchessboard.c
// draw chessboard pattern in SDL window <br/>

% gcc test_drawchessboard.c -o chess `pkg-config --cflags --libs sdl2`

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/SDL/result/screenshot_chess.png" width="300" /><br/>

## test_bmp.cpp
// read bmp image file <br/>
// show in SDL window <br/>

% g++ test_bmp.cpp parse_filename.cpp -o bmp `pkg-config --cflags --libs sdl2_image` <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/SDL/result/screenshot_uparrow.png" width="300" /><br/>

## example_image
draw png image and bmp image from image file <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/SDL/example_image/result/screenshot_mysdl.png" width="300" /><br/>

### Reference <br/>
- https://www.libsdl.org

