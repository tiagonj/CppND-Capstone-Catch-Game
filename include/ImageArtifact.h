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
    ImageArtifact() = delete;
    ImageArtifact(ImageArtifact&) = delete;
    ImageArtifact(ImageArtifact&&) = delete;
    ImageArtifact& operator=(ImageArtifact&) = delete;
    ImageArtifact& operator=(ImageArtifact&&) = delete;

  private:
    float _heightInPercent{0.0f};
    float _widthInPercent{0.0f};
};

#endif
