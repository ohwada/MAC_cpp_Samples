/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// draw png image and bmp image from image file

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#include <SDL.h>

#include "Window.h"
#include "Renderer.h"
#include "SpriteObject.h"


using namespace mysdl;

#define SDL_WINDOW_TITLE "MySDL"
#define SDL_WINDOW_WIDTH (640)
#define SDL_WINDOW_HEIGHT (360)

static Renderer *gRenderer = nullptr;


/**
 * input
 */
static bool input()
{
  SDL_Event event;

  /** NOTE: SDL_PollEvent does not sleep while SDL_WaitEvent sleep
      till event comes. SDL_WaitEvent is more relaxible than
      SDL_PollEvent. If input is combined with draw, SDL_WaitEvent
      cannot be used. */
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      return true;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_p: {
        static int pngX = 0;
        SpriteObject *png
          = new SpriteObject("char_p.png", pngX, 0, 100, 100);
        gRenderer->send(png);
        pngX += 48;
        break;
      }
      case SDLK_b: {
        static int bmpX = 200;
        SpriteObject *bmp
          = new SpriteObject("char_b.bmp", bmpX, 200, 100, 100);
        gRenderer->send(bmp);
        bmpX += 72;
        break;
      }
      default:
        break;
      }
      break;
    default:
      break;
    }
  }

  return false;
}


/**
 * main
 */
int main(int argc, char *argv[])
{
  Window window(SDL_WINDOW_TITLE, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT);
  gRenderer = window.getRenderer();

  while (1)
    if (input())
      break;

  return 0;
}
