#ifndef CATCH_GAME_IMAGE_ARTIFACT_H
#define CATCH_GAME_IMAGE_ARTIFACT_H

#include <string>

class ImageArtifact
{
  public:
    ImageArtifact(std::string imageFileName);
    ~ImageArtifact();
    float HalfHeightInPercent();
    float HalfWidthInPercent();

  private:
    ImageArtifact(ImageArtifact&) = delete;
    ImageArtifact(ImageArtifact&&) = delete;
    ImageArtifact& operator=(ImageArtifact&) = delete;
    ImageArtifact& operator=(ImageArtifact&&) = delete;

  private:
    float _heightInPercent{-1.0};
    float _widthInPercent{-1.0};
};

#endif
