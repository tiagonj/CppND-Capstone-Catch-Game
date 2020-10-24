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

    void Update(uint32_t updatesPerSecond, bool moveLeft, bool moveRight);
    float LeftEdgePosition();
    float RightEdgePosition();

  private:
    Catcher(Catcher &) = delete;
    Catcher(Catcher &&) = delete;
    Catcher &operator=(Catcher &) = delete;
    Catcher &operator=(Catcher &&) = delete;

    MoveDirection GetRequestedMoveDirection(bool moveLeft, bool moveRight);
    double GetVelocityDelta(double tickDurationInSeconds, MoveDirection requestedDirection);
    double GetNewVelocity(double velocityDeltaInPercentPerSecond, MoveDirection requestedDirection);
    void UpdatePositionAndVelocity(double tickDurationInSeconds, double newVelocity);
    float LeftEdgeForPosition(float position);
    float RightEdgeForPosition(float position);

  private:
    float _positionInPercent{0.5f};
    float _halfWidthInPercent{0.05f};
    double _velocityInPercentPerSecond{0.0}; // Negative: left; Positive: right
};

#endif
