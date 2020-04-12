/**
 * SDL Sample
 * 2020-03-01 K.OHWADA
 */

// original : https://www.hiroom2.com/2015/05/14/sdl2%E3%81%AEbmp%E7%94%BB%E5%83%8F%E3%81%A8png%E7%94%BB%E5%83%8F%E3%81%AE%E6%8F%8F%E7%94%BB%E5%87%A6%E7%90%86/#sec-2


#include "TextureRequest.h"

namespace mysdl {

std::map<Texture *, TextureRequest> TextureRequest::gMap;
Mutex TextureRequest::gMutex;

void TextureRequest::send(Texture *texture,
                         TextureRequestType type)
{
  gMutex.lock();
  gMap[texture] = TextureRequest(texture, type);
  gMutex.unlock();
}

void TextureRequest::recv(SDL_Renderer *renderer)
{
  gMutex.lock();
  for (std::map<Texture *, TextureRequest>::iterator
         i = gMap.begin(), e = gMap.end(); i != e; ++i) {
    TextureRequest req = i->second;
    switch (req.getType()) {
    case TEXTURE_REQUEST_TYPE_CREATE:
      req.create(renderer);
      break;
    case TEXTURE_REQUEST_TYPE_DESTROY:
      req.destroy();
      delete req.getTexture();
      break;
    default:
      break;
    }
  }
  gMap.clear();
  gMutex.unlock();
}

void TextureRequest::quit(SDL_Renderer *renderer)
{
  gMutex.lock();
  for (std::map<Texture *, TextureRequest>::iterator
         i = gMap.begin(), e = gMap.end(); i != e; ++i) {
    TextureRequest req = i->second;
    req.destroy();
    delete req.getTexture();
  }
  gMap.clear();
  gMutex.unlock();
}

};
