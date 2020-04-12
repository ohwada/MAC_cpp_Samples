/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_TEXTURE_H
#define __MYSDL_TEXTURE_H

#include <SDL.h>

namespace mysdl {

class Texture {
 private:
  SDL_Texture *mTexture;
  SDL_Surface *mSurface;
  SDL_Rect mRect;

 public:
  Texture() : mTexture(nullptr), mSurface(nullptr)
  {
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = 0;
    mRect.h = 0;
  }

  virtual ~Texture() {}

  SDL_Surface *getSurface()
  {
    return mSurface;
  }

  void setSurface(SDL_Surface *surface)
  {
    mSurface = surface;
    mRect.w = surface->w;
    mRect.h = surface->h;
  }

  SDL_Texture *getTexture()
  {
    return mTexture;
  }

  void setTexture(SDL_Texture *texture)
  {
    mTexture = texture;
  }

  SDL_Rect *getRect()
  {
    return &mRect;
  }

  bool createTexture(SDL_Renderer *renderer)
  {
    if (mTexture != nullptr)
      return false;
    mTexture = SDL_CreateTextureFromSurface(renderer, getSurface());
    return mTexture != nullptr;
  }
};

};

#endif /** __MYSDL_TEXTURE_H */
