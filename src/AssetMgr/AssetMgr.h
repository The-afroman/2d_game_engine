#ifndef ASSETMGR_H
#define ASSETMGR_H

#include <map>
#include <string>
#include <SDL2/SDL.h>

class AssetMgr {
  private:
    std::map<std::string, SDL_Texture*> textures;
  
    // TODO create map for fonts, audio
  public:
    AssetMgr();
    ~AssetMgr();

    void clearAssets();
    void addTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
    SDL_Texture* getTexture(const std::string assetId);

};

#endif