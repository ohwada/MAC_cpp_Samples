/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */


// read bmp image file
// show in SDL window
// reference : https://k38.hatenadiary.jp/entry/2018/10/19/011926


#include <string> 
#include<iostream>

#include <SDL.h>
#include <SDL_image.h>

#include"parse_filename.hpp"

using namespace std;

// global
bool isRunning = false;

/**
 * PollEventLoop
 */
void PollEventLoop()
{

    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {

            if (e.type == SDL_QUIT) {
                    isRunning = false;
                	break;
            }

            if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
                    isRunning = false;
                	break;
            }

    } // while

    return;
}


/**
 * main
 */
int main( int argc, char** argv)
{

    const int WIN_WIDTH = 500;
    const int WIN_HEIGHT = 500;
    const int WIN_POS_X = 100;
    const int WIN_POS_Y = 100;


        if(argc < 2) {
            cerr << "Usage: " << argv[0] << " <inputImageFile> "  << endl;
            return EXIT_FAILURE;
        }

        string input = argv[1];

        string fname = getFileNameWithExt(input);

        string win_title = "SDL: " + fname;


        //Initialize SDL
        if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) {
            cout << "SDL_Init Faild: " << SDL_GetError() << endl;
            return EXIT_FAILURE;
        }


        //Create window
        SDL_Window*window = SDL_CreateWindow(
            win_title.c_str(),
            WIN_POS_X, 
            WIN_POS_Y, 
            WIN_WIDTH, 
            WIN_HEIGHT,
            0 );

        if(!window) {
            cout << "SDL_CreateWindow Faild: " << SDL_GetError() << endl;
            return EXIT_FAILURE;
        }


        // CreateRenderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
		if( !renderer){
            cout << "SDL_CreateRenderer Faild: " << SDL_GetError() << endl;
            return EXIT_FAILURE;
		}


        // load image
        SDL_Surface* image_surface = SDL_LoadBMP(input.c_str());
        if(!image_surface) {
                cout << "SDL_LoadBMP Faild: " << input << " : "<< SDL_GetError() << endl;
                return EXIT_FAILURE;
        }


        SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
        if(!image_texture) {
                cout << "SDL_CreateTextureFromSurface Faild: " << SDL_GetError() << endl;
                return EXIT_FAILURE;
        }


        // get width and height
        int img_width = 0;
        int img_height = 0;

        SDL_QueryTexture(image_texture, NULL, NULL, &img_width, &img_height);

        if((img_width==0)||(img_height==0)){
                cout << "SDL_QueryTexture Faild: " << SDL_GetError() << endl;
                return EXIT_FAILURE;
        }

        cout << "load image: " << input << " ( "<< img_width << " x "<< img_height << " ) " << endl;


        SDL_Rect imageRect = (SDL_Rect){0, 0 ,img_width, img_height};
        SDL_Rect drawRect = (SDL_Rect){0, 0, img_width, img_height};

        // set image
        SDL_RenderCopy(renderer, image_texture, &imageRect, &drawRect);

        // draw image
        SDL_RenderPresent(renderer);

        // wait to input key
        isRunning = true;
        while (isRunning) {
            PollEventLoop();
        }

        // cleanup
        SDL_FreeSurface(image_surface);
        SDL_DestroyTexture(image_texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return EXIT_SUCCESS;
}
