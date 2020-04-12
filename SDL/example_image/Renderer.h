/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_RENDERER_H
#define __MYSDL_RENDERER_H

#include <SDL.h>
#include <deque>

#include "Mutex.h"
#include "Object.h"
#include "TextureRequest.h"


namespace mysdl {

/** NOTE: Windows on KVM cannot call direct3D.
    Then SDL_RENDERER_SOFTWARE will be needed. */
#ifdef NEED_RENDERER_SOFTWARE
#define SDL_RENDERER_FLAGS (SDL_RENDERER_SOFTWARE)
#else
#define SDL_RENDERER_FLAGS (0)
#endif

class Renderer {
 private:
  std::deque<Object *> mQueue;
  SDL_Renderer *mRenderer;
  Mutex mMutex;

 public:
  Renderer(SDL_Window *window)
  {
    mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_FLAGS);
  }

  ~Renderer()
  {
    for (Object *object : mQueue)
      delete object;
    TextureRequest::quit(mRenderer);
    SDL_DestroyRenderer(mRenderer);
  }

  void recv()
  {
    mMutex.lock();
    TextureRequest::recv(mRenderer);
    mMutex.unlock();
  }

  void send(Object *object)
  {
    mMutex.lock();
    mQueue.push_back(object);
    mMutex.unlock();
  }

  void draw()
  {
    /** NOTE: Clear render with Color (0, 0, 0, 0) for erasing
        current drawing. */
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

    mMutex.lock();

    for (Object *object : mQueue) {
      Texture *texture = object->getTexture();
      SDL_Texture *sdlTexture = texture->getTexture();
      if (sdlTexture == nullptr)
        continue;
      SDL_Rect *src = texture->getRect();
      SDL_Rect *dst = object->getRect();
      SDL_RenderCopy(mRenderer, sdlTexture, src, dst);
    }

    mMutex.unlock();

    /** NOTE: Update drawing (switch double buffer). */
    SDL_RenderPresent(mRenderer);

    /** NOTE: Sleep 10 msec. */
    SDL_Delay(10);
  }
};

};

#endif /** __MYSDL_RENDERER_H */
