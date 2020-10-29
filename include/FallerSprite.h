#ifndef CATCH_GAME_FALLER_SPRITE_H
#define CATCH_GAME_FALLER_SPRITE_H

#include <string>

class FallerSprite
{
  public:
    FallerSprite(std::string imageFileName);
    ~FallerSprite();
    float HalfHeightInPercent();
    float HalfWidthInPercent();

  private:
    FallerSprite() = delete;
    FallerSprite(FallerSprite&) = delete;
    FallerSprite(FallerSprite&&) = delete;
    FallerSprite& operator=(FallerSprite&) = delete;
    FallerSprite& operator=(FallerSprite&&) = delete;

  private:
    float _heightInPercent{0.0f};
    float _widthInPercent{0.0f};
};

#endif
