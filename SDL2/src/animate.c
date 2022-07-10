/**
 * animate.c
 * 2022-06-01 K.OHWADA
 */

// animate image
// reference : https://k38.hatenadiary.jp/entry/2018/10/31/235248

// gcc animate.c -o animate `pkg-config --cflags --libs sdl2` -lSDL2_image


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * main
 */
int main (int argc, char *argv[]) 
{
const char IMAGE_PATH[] = "images/walkcat.jpg";
const char TITLE[] = "SDL2: Draw Image";
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;
const int IMAGE_WIDTH = 16; 
const int IMAGE_HEIGHT = 16; 

// draw an image with size of 16 x 16 in size of 64 x 64
const int  DRAW_WIDTH = 64;
 const int  DRAW_HEIGHT = 64;

// the number of images connected horizontally
const int NUM_WIDTH = 4;

// map color: magenta
const Uint8 MR = 255;
const Uint8 MG = 0;
const Uint8 MB = 255;

// draw color: gray
const Uint8 DR = 200;
const Uint8 DG = 200;
const Uint8 DB = 200;
const Uint8 DA = 255;

    SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *image_texture = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { 
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }   

    window = SDL_CreateWindow( 
        (char *)TITLE, 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN );

    if(!window) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
               return EXIT_FAILURE;
    } 

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if( !renderer) {
                printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
                return EXIT_FAILURE;
            } 

    image = IMG_Load( (char *)IMAGE_PATH );
    if(!image) {
        printf("IMG_Load: %s\n", IMG_GetError());
               return EXIT_FAILURE;
    }

    // set Transparent color 
    SDL_SetColorKey( image, SDL_TRUE, SDL_MapRGB(image->format, MR, MG, MB));

    image_texture = SDL_CreateTextureFromSurface(renderer, image);

       if( !image_texture) {
                printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
                return EXIT_FAILURE;
        } 


    SDL_SetRenderDrawColor(renderer,  DR,  DG,  DB,  DA);

    int iw,ih;     
    SDL_QueryTexture(image_texture, NULL, NULL, &iw, &ih);

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

    const int MAX_FRAME = 6000;
    const int ANIME_CYCLE = 60;
    int frame = 0;

    // main loop
    while (frame <  MAX_FRAME) 
{
// cut out one from the four that are connected horizontally
        int ix = ((frame / ANIME_CYCLE) % NUM_WIDTH) *  IMAGE_WIDTH;
        SDL_Rect imageRect = (SDL_Rect){ix, 0, IMAGE_WIDTH, IMAGE_HEIGHT};

   // center
        int dx = SCREEN_WIDTH/2 - iw/2;
        int dy = SCREEN_HEIGHT/2 - ih/2;
        SDL_Rect drawRect = (SDL_Rect){dx, dy, DRAW_WIDTH,
        DRAW_HEIGHT};

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image_texture, &imageRect, &drawRect);
        SDL_RenderPresent(renderer);

        frame += 1;

    } // while

    IMG_Quit();
    SDL_FreeSurface(image);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;

}

