 /**
 * image.c
 * 2022-06-01 K.OHWADA
 */

// draw image
// reference : https://k38.hatenadiary.jp/entry/2018/10/19/011926

// gcc image.c -o image  `pkg-config --cflags --libs sdl2` -lSDL2_image

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


 /**
 * main
 */
int main( int argc, char* args[] ) 
{
const char IMAGE_PATH[] = "images/cat.bmp";
const char TITLE[] = "SDL2: Draw Image";
const int WIDTH = 320;
const int HEIGHT = 240;
const Uint32 DELAY = 10000; // 10 sec

// color  "magenta" is not used for pixel art (cat.bmp)
// in order to make the background color transparent using the SDL2 function

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

// allows to read images in JPG and PNG formats
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);

    if( (initted&flags) != flags) {
        printf("IMG_Init: Failed to initialize JPG and PNG import \n");
        printf("IMG_Init: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

        //Create window
        window = SDL_CreateWindow( 
            (char *)TITLE,
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            WIDTH, 
            HEIGHT, 
            SDL_WINDOW_SHOWN );

        if( !window) {
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

        int iw,ih;
        SDL_QueryTexture(image_texture, NULL, NULL, &iw, &ih);
        SDL_Rect imageRect=(SDL_Rect){0, 0, iw, ih};

    // center
        int x = WIDTH/2 - iw/2;
        int y = HEIGHT/2 - ih/2;
            SDL_Rect drawRect=(SDL_Rect){ x, y, iw, ih};

            SDL_SetRenderDrawColor(renderer, DR, DG, DB, DA);
       
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, image_texture, &imageRect, &drawRect);
            SDL_RenderPresent(renderer);


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


    SDL_Delay(  DELAY );

    IMG_Quit();
    SDL_FreeSurface(image);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}
