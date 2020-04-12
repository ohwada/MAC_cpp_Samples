/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_RENDER_THREAD_H
#define __MYSDL_RENDER_THREAD_H

#include <SDL.h>

#include "Renderer.h"


namespace mysdl {

extern int runRenderThread(void *);

class RenderThread {
 private:
  SDL_Window *mWindow;
  Renderer *mRenderer;
  SDL_semaphore *mSemaphore;
  SDL_Thread *mThread;
  bool mStop;

 public:
  RenderThread(SDL_Window *window) : mWindow(window), mStop(false)
  {
    mSemaphore = SDL_CreateSemaphore(0);
    mThread = SDL_CreateThread(runRenderThread, "RenderThread",
                               (void *) this);
    SDL_SemWait(mSemaphore);
  }

  ~RenderThread()
  {
    if (!mStop)
      stop();
    SDL_DestroySemaphore(mSemaphore);
  }

  void initialize()
  {
    mRenderer = new Renderer(mWindow);
    SDL_SemPost(mSemaphore);
  }

  void finalize()
  {
    delete mRenderer;
  }

  void run()
  {
    while (!mStop) {
      mRenderer->recv();
      mRenderer->draw();
      SDL_Delay(10);
    }
  }

  void stop()
  {
    int ret;
    mStop = true;
    SDL_WaitThread(mThread, &ret);
    mThread = nullptr;
  }

  Renderer *getRenderer()
  {
    return mRenderer;
  }
};

};

#endif /** __MYSDL_RENDER_THREAD_H */
