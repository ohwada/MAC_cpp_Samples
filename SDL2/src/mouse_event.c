/**
 * mouse_event.c
 * 2022-06-01 K.OHWADA
 */

// move the image with mouse click
// reference : https://k38.hatenadiary.jp/entry/2018/11/13/233300

// gcc mouse_event.c -o mouse  `pkg-config --cflags --libs sdl2` -lSDL2_image 


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/**
 * typedef CONTROL
 */
typedef enum {right, left} CONTROL;


/**
 * main
 */
int main (int argc, char *argv[]) 
{
const char IMAGE_PATH[] = "images/walkcat.jpg";
const char TITLE[] = "SDL2: Mouse Event";
const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 360;
const int IMAGE_WIDTH = 16;
const int IMAGE_HEIGHT = 16;
const int  DRAW_WIDTH = 64;
 const int  DRAW_HEIGHT = 64;
const int NUM_WIDTH = 4;
const int DRAW_WIDTH_CENTER  = DRAW_WIDTH / 2;
const int DRAW_HEIGHT_CENTER  = DRAW_HEIGHT / 2;

// map color: magenta
const Uint8 MR = 255;
const Uint8 MG = 0;
const Uint8 MB = 255;

// draw color: gray
const Uint8 DR = 200;
const Uint8 DG = 200;
const Uint8 DB = 200;
const Uint8 DA = 255;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *image_texture = NULL;


    SDL_Point window_position = {
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    };


    SDL_Point window_size = {SCREEN_WIDTH, SCREEN_HEIGHT};


    SDL_Point mouse_position = {DRAW_WIDTH_CENTER, DRAW_WIDTH_CENTER};

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow( 
        (char *)TITLE, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN );

    if( !window ) {
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


    SDL_SetRenderDrawColor(renderer, DR, DG, DB, DA);

    int iw,ih;
    SDL_QueryTexture(image_texture, NULL, NULL, &iw, &ih);

   const  int ANIME_CYCLE = 60;
    int frame = 0;

    CONTROL status = right;

    // main loop
    while (1) 
{
// cut out one from the four that are connected horizontally
        int x = ((frame / ANIME_CYCLE) % NUM_WIDTH) * IMAGE_WIDTH;
        SDL_Rect imageRect=(SDL_Rect){x, 0, 
        IMAGE_WIDTH, 
        IMAGE_HEIGHT};
        SDL_Rect drawRect=(SDL_Rect){mouse_position.x - (DRAW_WIDTH_CENTER),
                                     mouse_position.y - (DRAW_HEIGHT_CENTER),
                                     DRAW_WIDTH,
                        DRAW_HEIGHT};

        SDL_RenderClear(renderer);
        if (status == right) {
            SDL_RenderCopy(renderer, image_texture, &imageRect, &drawRect);
        } else if (status == left) {
            SDL_RenderCopyEx(renderer, image_texture, &imageRect, &drawRect, 0 , NULL ,SDL_FLIP_HORIZONTAL);
        }
        SDL_RenderPresent(renderer);

        if (frame <= ANIME_CYCLE * 4) {
            frame += 1;
        } else{
            frame = 0;
        }

        // event handling
        SDL_Event e;
        if ( SDL_PollEvent(&e) ) {
            if (e.type == SDL_QUIT){
                break;
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                break;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
// get the mouse position on the window
                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
                status = right;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
                status = left;
            }
        }
    }

    IMG_Quit();
    SDL_FreeSurface(image);
    SDL_DestroyTexture(image_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

