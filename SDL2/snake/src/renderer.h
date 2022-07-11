#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "types.h"

BOOL RendererInitialise(void);
void RendererFree(void);
void RendererClear(void);
void RendererDraw(void);
void RendererGetWindowSize(int * pW, int * pH);
void RendererDrawText(char * pText, const SDL_Color colour, const ushort x, const ushort y, const BOOL isTitle);
void RendererDrawTextBlended(char * pText, const SDL_Color colour, const ushort x, const ushort y, const BOOL isTitle);

SDL_Renderer * GetRenderer(void);
TTF_Font * GetFont(void);

#endif // !RENDERER_H
