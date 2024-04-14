#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

struct SpriteComponent {
  std::string assetId;
  int width;
  int height;
  SDL_Rect srcRect;

  SpriteComponent(std::string assetId = "", int width = 1, int height = 1,
                  int srcRectX = 0, int srcRectY = 0) {
    this->width = width;
    this->height = height;
    this->srcRect = {srcRectX, srcRectY, width, height};
    this->assetId = assetId;
  }
};

#endif