/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#ifndef __MYSDL_TEXTURE_REQUEST_H
#define __MYSDL_TEXTURE_REQUEST_H

#include <map>

#include "Texture.h"
#include "Mutex.h"

namespace mysdl {

enum TextureRequestType {
  TEXTURE_REQUEST_TYPE_NONE,
  TEXTURE_REQUEST_TYPE_CREATE,
  TEXTURE_REQUEST_TYPE_DESTROY,
};

class TextureRequest {
 private:
  static std::map<Texture *, TextureRequest> gMap;
  static Mutex gMutex;

  Texture *mTexture;
  SDL_Texture *mSDLTexture;
  SDL_Surface *mSDLSurface;
  TextureRequestType mType;

 public:
  static void send(Texture *, TextureRequestType);
  static void recv(SDL_Renderer *);
  static void quit(SDL_Renderer *);

  TextureRequest() : mTexture(nullptr), mSDLTexture(nullptr),
    mSDLSurface(nullptr), mType(TEXTURE_REQUEST_TYPE_NONE) {}
  TextureRequest(Texture *texture, TextureRequestType type)
    : mTexture(texture), mSDLTexture(nullptr),
    mSDLSurface(texture->getSurface()), mType(type) {}

  Texture *getTexture() const
  {
    return mTexture;
  }

  SDL_Surface *getSDLSurface() const
  {
    return mSDLSurface;
  }

  SDL_Texture *getSDLTexture() const
  {
    return mSDLTexture;
  }

  const TextureRequestType getType() const
  {
    return mType;
  }

  void create(SDL_Renderer *renderer)
  {
    mTexture->createTexture(renderer);
    mSDLTexture = mTexture->getTexture();
    mSDLSurface = mTexture->getSurface();
  }

  void destroy()
  {
    if (mSDLTexture != nullptr) {
      SDL_DestroyTexture(mSDLTexture);
      mSDLTexture = nullptr;
    }

    if (mSDLSurface != nullptr) {
      SDL_FreeSurface(mSDLSurface);
      mSDLSurface = nullptr;
    }
  }

  TextureRequest &operator=(const TextureRequest &req)
  {
    mTexture = req.getTexture();
    mSDLTexture = req.getSDLTexture();
    mSDLSurface = req.getSDLSurface();
    mType = req.getType();
    return *this;
  }
};

};

#endif /** __MYSDL_TEXTURE_REQUEST_H */
