 /**
 * font.c
 * 2022-06-01 K.OHWADA
 */

// draw text with font
// reference : https://k38.hatenadiary.jp/entry/2018/10/12/062049

// gcc font.c -o font  `pkg-config --cflags --libs sdl2` -lSDL2_ttf


 #include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


 /**
 * main
 */
int main( int argc, char* args[] ) 
{
const char FONT_PATH[] = "fonts/PixelMplus12-Regular.ttf";
const int WIDTH = 480;
const int HEIGHT = 360;
const char TITLE[] = "SDL2: Draw Text";
const char HELLO[] = "Hello World!";
const int PTSIZE = 40;
const Uint32 DELAY = 10000; // 10 sec

// white
const SDL_Color FG = {255,255,255,255};

// black
const Uint8 R = 0;
const Uint8 G = 0;
const Uint8 B = 0;
const Uint8 A= 255;


 SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Event ev;

    TTF_Font *font;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    } 

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

            //Initialize TTF
            if ( TTF_Init() < 0 ) {
                printf("TTFcould not initialize! TTF_Error: %s\n", TTF_GetError());
                return EXIT_FAILURE;
            } 


                font = TTF_OpenFont(FONT_PATH, PTSIZE);

                if (!font) {
                    printf("TTF_OpenFont: %s\n", TTF_GetError());
                    return EXIT_FAILURE;
                }


                // drawing without outline
                // TTF_SetFontOutline(font, 1);

                    surface = TTF_RenderUTF8_Blended(font,
                    (char *)HELLO, FG);

             if( !surface) {
                printf( "Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
                return EXIT_FAILURE;
            } 

        
                    texture = SDL_CreateTextureFromSurface(renderer, surface);

             if( ! texture) {
                printf( "Texture could not be created! SDL_Error: %s\n", SDL_GetError() );
                return EXIT_FAILURE;
            } 

                    SDL_SetRenderDrawColor(renderer, R, G, B, A);
                    SDL_RenderClear(renderer);

                // get the size of the Texture that draw the text    
                    int iw,ih;
                    SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
                    SDL_Rect txtRect=(SDL_Rect){0, 0, iw, ih};

        // center
            int x = WIDTH/2 - iw/2;
            int y = HEIGHT/2 - ih/2;
                    SDL_Rect pasteRect=(SDL_Rect){ x , y, iw, ih};

                    //Textureを描写する      
                    //描写元の描写する部分,描写先の描写する部分)      
                    //サイズが違うと勝手にTextureを伸展してくれる  


                // Draw Texture
                // the part drawn by the depiction source, 
                // the part drawn by the depiction destination
                // if the size is different, texture will be extended    
                    SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);    
                    SDL_RenderPresent(renderer);


// it dont seem to  display window
// without this loop
// https://www.webcyou.com/?p=10388
SDL_Event e;
while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            break;
        }
} // while


    SDL_Delay(DELAY);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    return EXIT_SUCCESS;

}
