/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_OBJECT_H
#define __MYSDL_OBJECT_H

#include "Texture.h"
#include "TextureRequest.h"

namespace mysdl {

class Object {
 private:
  Texture *mTexture;
  SDL_Rect mRect;

 public:
  Object(int x, int y, int w, int h) : mTexture(nullptr)
  {
    setRect(x, y, w, h);
  }

  Object(Texture *texture, int x, int y, int w, int h)
    : mTexture(texture)
  {
    TextureRequest::send(mTexture, TEXTURE_REQUEST_TYPE_CREATE);
    setRect(x, y, w, h);
  }

  virtual ~Object()
  {
    TextureRequest::send(mTexture, TEXTURE_REQUEST_TYPE_DESTROY);
  }

  Texture *getTexture() const
  {
    return mTexture;
  }

  void setTexture(Texture *texture)
  {
    mTexture = texture;
  }

  SDL_Rect *getRect()
  {
    return &mRect;
  }

  void setRect(int x, int y, int w, int h)
  {
    mRect.x = x;
    mRect.y = y;
    mRect.w = w;
    mRect.h = h;
  }
};

};

#endif /** __MYSDL_OBJECT_H */
