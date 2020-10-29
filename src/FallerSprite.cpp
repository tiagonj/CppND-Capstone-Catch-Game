#include "FallerSprite.h"

FallerSprite::FallerSprite(std::string imageFileName)
{
    // TODO
    (void)imageFileName;
    // TODO fix below
    _heightInPercent = 0.025f;
    _widthInPercent = 0.025f;
}

FallerSprite::~FallerSprite()
{
    // TODO
}

float FallerSprite::HalfHeightInPercent()
{
    return _heightInPercent / 2.0f;
}

float FallerSprite::HalfWidthInPercent()
{
    return _widthInPercent / 2.0f;
}
