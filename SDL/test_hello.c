/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// display SDL window
// original : https://wiki.libsdl.org/SDL_CreateWindow#Code_Examples

// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>


// global
int isRunning = 0;


/**
 * PollEventLoop
 */
void PollEventLoop()
{

    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {

            if (e.type == SDL_QUIT) {
                    isRunning = 0;
                	break;
            }

            if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
                    isRunning = 0;
                	break;
            }

    } // while

    return;
}


/**
 * main
 */
int main( int argc, char** argv )
{

	const int WIN_WIDTH = 320;
	const int WIN_HEIGHT = 240;
	const int WIN_X = 100;
	const int WIN_Y = 100;
	const char* WIN_TITLE = "SDL: Hello";

    // show SDL Version
    SDL_version compiled;
    SDL_version linked;

    SDL_VERSION(&compiled);
    SDL_GetVersion(&linked);
    printf("SDL compiled Version %d.%d.%d \n",
           compiled.major, compiled.minor, compiled.patch);
    printf("SDL linked Version %d.%d.%d \n",
           linked.major, linked.minor, linked.patch);


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 1;
	}

	//Create window
	SDL_Window* window = SDL_CreateWindow(
		WIN_TITLE, 
		WIN_X,
		WIN_Y, 
		WIN_WIDTH, 	
		WIN_HEIGHT, 
		0 );

		if( !window) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return 1;
		}

		//Get window surface
		SDL_Surface*screenSurface = SDL_GetWindowSurface( window );
		if( !screenSurface) {
			printf( "SDL_GetWindowSurface: %s\n", SDL_GetError() );
			return 1;
		}

			//Fill the surface White
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );


        // wait to input key
        isRunning = 1;
        while (isRunning) {
            PollEventLoop();
        }


		// cleanup
		SDL_DestroyWindow( window );
		SDL_Quit();

		return 0;
}

