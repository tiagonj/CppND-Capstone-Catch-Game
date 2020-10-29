#ifndef CATCH_GAME_FALLER_H
#define CATCH_GAME_FALLER_H

#include "FallerSprite.h"

#include <cstdint>
#include <memory>

// Interface/base class for Faller objects
class Faller
{
  public:
    ~Faller();
    virtual void Update(double timeDeltaInSeconds, float xAccelInUnitsPerSecSquared,
                        float yAccelInUnitsPerSecSquared); // Default update (can be overriden)
    FallerSprite& GetImageArtifact() const;
    float UpPosition() const;
    float DownPosition() const;
    float LeftPosition() const;
    float RightPosition() const;
    uint32_t RewardPoints() const;

  protected:
    Faller(std::shared_ptr<FallerSprite>& img, float x, float vx, float vy, uint32_t rewardPoints);
    void UpdatePosAndVel(double timeDeltaInSeconds, float& pos, float& vel, float accel);
    void UpdateXPosAndVel(double timeDeltaInSeconds, float accel);

  private:
    void SolveQuadraticEq(float a, float b, float c, float& smallestSolution,
                          float& largestSolution);
    Faller() = delete;
    Faller(Faller&) = delete;
    Faller(Faller&&) = delete;
    Faller& operator=(Faller&) = delete;
    Faller& operator=(Faller&&) = delete;

  protected:
    float _xPosition; // Note: positions are in normalised units (0.0 ~ 1.0)
    float _yPosition;
    float _xVelocityInUnitsPerSecond;
    float _yVelocityInUnitsPerSecond;
    uint32_t _rewardPoints;

  private:
    std::shared_ptr<FallerSprite> _img;
};

#endif
