#include "ImageArtifact.h"

ImageArtifact::ImageArtifact(std::string imageFileName)
{
    // TODO
    (void)imageFileName;
    //_heightInPercent = xxx;
    //_widthInPercent = xxx;
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
