#include "ImageArtifact.h"

ImageArtifact::ImageArtifact(std::string imageFileName)
{
    // TODO
    (void)imageFileName;
    // TODO fix below
    _heightInPercent = 0.025f;
    _widthInPercent = 0.025f;
}

ImageArtifact::~ImageArtifact()
{
    // TODO
}

float ImageArtifact::HalfHeightInPercent()
{
    return _heightInPercent / 2.0f;
}

float ImageArtifact::HalfWidthInPercent()
{
    return _widthInPercent / 2.0f;
}
