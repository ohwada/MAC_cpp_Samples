/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_WINDOW_H
#define __MYSDL_WINDOW_H

#include <SDL.h>

#include "RenderThread.h"

namespace mysdl {

class Window {
 private:
  SDL_Window *mWindow;
  RenderThread *mThread;

 public:
  Window(const char *title, int width, int height)
  {
    SDL_Init(SDL_INIT_EVERYTHING);
    mWindow = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               width, height, 0);
    mThread = new RenderThread(mWindow);
  }

  ~Window()
  {
    delete mThread;
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
  }

  Renderer *getRenderer()
  {
    return mThread->getRenderer();
  }
};

};

#endif /** __MYSDL_WINDOW_H */
