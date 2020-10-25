#ifndef CATCH_GAME_FALLER_H
#define CATCH_GAME_FALLER_H

#include "ImageArtifact.h"

#include <cstdint>
#include <memory>

// Interface/base class for Faller objects
class Faller
{
  public:
    ~Faller();
    virtual void Update(double timeDeltaInSeconds, float xAccelInPercentPerSecSquared,
                        float yAccelInPercentPerSecSquared); // Default update (can be overriden)
    ImageArtifact &GetImageArtifact() const;
    float UpPositionInPercent() const;
    float DownPositionInPercent() const;
    float LeftPositionInPercent() const;
    float RightPositionInPercent() const;
    uint32_t RewardPoints() const;

  protected:
    Faller(std::shared_ptr<ImageArtifact> &img, float x, float vx, float vy, uint32_t rewardPoints);
    void UpdatePosAndVel(double timeDeltaInSeconds, float &pos, float &vel, float accel);
    void UpdateXPosAndVel(double timeDeltaInSeconds, float accel);

  private:
    void SolveQuadraticEq(float a, float b, float c, float &smallestSolution,
                          float &largestSolution);
    Faller() = delete;
    Faller(Faller &) = delete;
    Faller(Faller &&) = delete;
    Faller &operator=(Faller &) = delete;
    Faller &operator=(Faller &&) = delete;

  protected:
    float _xPositionInPercent;
    float _yPositionInPercent;
    float _xVelocityInPercentPerSecond;
    float _yVelocityInPercentPerSecond;
    uint32_t _rewardPoints;

  private:
    std::shared_ptr<ImageArtifact> _img;
};

#endif
