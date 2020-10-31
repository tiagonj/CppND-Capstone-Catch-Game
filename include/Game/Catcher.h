#ifndef CATCH_GAME_CATCHER_H
#define CATCH_GAME_CATCHER_H

#include <cstdint>

enum MoveDirection
{
    _kMoveLeft = -1,
    _kNoMovement = 0,
    _kMoveRight = 1,
};

class Catcher
{
  public:
    Catcher();
    ~Catcher();

    void Update(double tickDurationInSeconds, bool moveLeft, bool moveRight);
    float LeftEdgePosition();
    float RightEdgePosition();

  private:
    Catcher(Catcher&) = delete;
    Catcher(Catcher&&) = delete;
    Catcher& operator=(Catcher&) = delete;
    Catcher& operator=(Catcher&&) = delete;

    MoveDirection GetRequestedMoveDirection(bool moveLeft, bool moveRight);
    double GetVelocityDelta(double tickDurationInSeconds, MoveDirection requestedDirection);
    double GetNewVelocity(double velocityDeltaInUnitsPerSecond, MoveDirection requestedDirection);
    void UpdatePositionAndVelocity(double tickDurationInSeconds, double newVelocity);
    float LeftEdgeForCentrePosition(float centrePosition);
    float RightEdgeForCentrePosition(float centrePosition);

  private:
    float _centrePosition{0.5f};           // Note: positions are in normalised units (0.0 ~ 1.0)
    float _halfWidth{0.05f};               // In normalised units
    double _velocityInUnitsPerSecond{0.0}; // Negative: left; Positive: right
};

#endif
