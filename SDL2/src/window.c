 /**
 * window.c
 * 2022-06-01 K.OHWADA
 */

// draw simple window
// referemce : https://www.webcyou.com/?p=10388

// gcc window.c -o window  `pkg-config --cflags --libs sdl2`  


#include <SDL2/SDL.h>
#include <stdio.h>


 /**
 * main
 */
int main( int argc, char* args[] ) 
{
const char TITLE[] = "SDL2: Hello";
const int WIDTH = 320;
const int HEIGHT = 240;
const Uint32  DELAY = 3000; // 3 sec


    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s \n", SDL_GetError() );
        return EXIT_FAILURE;
    }
 
    SDL_Window *window = SDL_CreateWindow(
        (char *)TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN );
 
    if (!window) {
        printf("Could not create window: %s \n", SDL_GetError());
        return EXIT_FAILURE;
    }
 

// it dont seem to  display window
// without this loop
// https://www.webcyou.com/?p=10388
SDL_Event e;
while(SDL_PollEvent(&e)) 
{
    if (e.type == SDL_QUIT) {
            break;
        }
    } // while
 
    SDL_Delay(DELAY); 
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
