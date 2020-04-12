/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_MUTEX_H
#define __MYSDL_MUTEX_H

#include <SDL.h>

namespace mysdl {

/** NOTE: Not support for platform which has no thread id. */
class Mutex {
 private:
  SDL_mutex *mMutex;
  SDL_threadID mOwner;

 public:
  Mutex() : mOwner(0)
  {
    mMutex = SDL_CreateMutex();
  }

  ~Mutex()
  {
    SDL_DestroyMutex(mMutex);
  }

  bool hasLock()
  {
    return mOwner == SDL_ThreadID();
  }

  bool lock()
  {
    if (SDL_LockMutex(mMutex) != 0)
      return false;
    mOwner = SDL_ThreadID();
    return true;
  }

  bool unlock()
  {
    if (mOwner != SDL_ThreadID())
      return false;
    mOwner = 0;
    return SDL_UnlockMutex(mMutex) == 0;
  }
};

};

#endif /** __MYSDL_MUTEX_H */
