#include "asset_mgr.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Logger/logger.h"

AssetMgr::AssetMgr() { Logger::info("AssetMgr created"); }

AssetMgr::~AssetMgr() {
  clearAssets();
  Logger::info("AssetMgr detroyed");
}

void AssetMgr::clearAssets() {
  for (auto texture : textures) {
    SDL_DestroyTexture(texture.second);
  }
  textures.clear();
}

void AssetMgr::addTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath) {
  SDL_Surface *surface = IMG_Load(filePath.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  // add the texture to the map
  textures.emplace(assetId, texture);
  Logger::info("texture: " + assetId + " added to AssetMgr");
}

SDL_Texture *AssetMgr::getTexture(const std::string assetId) { return textures[assetId]; }