// change log
// 2022-06-01 K.OHWADA
// cancekked Full Screen Mode
// change SDL_WINDOW_FULLSCREEN_DESKTOP
// to SDL_WINDOW_SHOWN 

#include "renderer.h"
#include <stdio.h>

#include "globals.h"

// "Private" variables
static SDL_Window * pWindow = NULL;
static SDL_Renderer * pRenderer = NULL;
static TTF_Font * pFont = NULL;

// Create the game window.
// Initialise the font and renderer
// Return false if initialisation fails
BOOL RendererInitialise(void)
{
// In debug mode, create borderless fullscreen
// Otherwise the fullscreen will fuck with
// window switching into the debugger
// In release, just make a full screen
#ifdef DEBUG
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    const int MAX_WIDTH  = mode.w;
    const int MAX_HEIGHT = mode.h;

    pWindow = SDL_CreateWindow("Rainbow snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAX_WIDTH, MAX_HEIGHT, SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
#else
        pWindow = SDL_CreateWindow("Rainbow snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    WIN_WIDTH,  
    WIN_HEIGHT, 
//SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_WINDOW_SHOWN );
#endif // DEBUG

    if(!pWindow)
    {
        goto InitialiseRenderer_error;
    }
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(!pRenderer)
    {
        goto InitialiseRenderer_error;
    }
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);
    if(TTF_Init() != 0)
    {
        goto InitialiseRenderer_error;
    }

    pFont = TTF_OpenFont("font.ttf", 32);
    if(!pFont)
    {
        goto InitialiseRenderer_error;
    }

    return TRUE;

InitialiseRenderer_error:
    printf("InitialiseRenderer error: %s\n", SDL_GetError());
    return FALSE;
}

// Free all rendering resources
// Destroy game window
void RendererFree(void)
{
    if(pFont)
    {
        TTF_CloseFont(pFont);
    }
    if(pRenderer)
    {
        SDL_DestroyRenderer(pRenderer);
    }
    if(pWindow)
    {
        SDL_DestroyWindow(pWindow);
    }
}

// Clear the window screen
void RendererClear(void)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(pRenderer);
}

// Draw the present renderer
void RendererDraw(void)
{
    SDL_RenderPresent(pRenderer);
}

// Return the window size
void RendererGetWindowSize(int * pW, int * pH)
{
    if(pWindow)
    {
        SDL_GetWindowSize(pWindow, pW, pH);
    }
}

// Return pointer to the renderer
SDL_Renderer * GetRenderer(void)
{
    return pRenderer;
}

// Return the pointer to the font
TTF_Font * GetFont(void)
{
    return pFont;
}

// Draw selected text
void RendererDrawText(char * pText, const SDL_Color colour, const ushort x, const ushort y, const BOOL isTitle)
{
    SDL_Rect r;
    TTF_SizeText(pFont, pText, &r.w, &r.h);

    if(isTitle)
    {
        r.y -= r.h;
        r.w *= 2;
        r.h *= 2;
    }

    r.x = x - (r.w / 2);
    r.y = y - (r.h * 1.5);

    if(isTitle)
    {
        r.y -= (r.h / 2);
    }

    SDL_Surface * pTextSurface = TTF_RenderText_Solid(pFont, pText, colour);
    SDL_Texture * pTextTexture = SDL_CreateTextureFromSurface(pRenderer, pTextSurface);
    SDL_RenderCopy(pRenderer, pTextTexture, NULL, &r);
    SDL_FreeSurface(pTextSurface);
    SDL_DestroyTexture(pTextTexture);
}
