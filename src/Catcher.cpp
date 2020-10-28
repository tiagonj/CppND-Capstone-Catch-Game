#include "Catcher.h"
#include "PositionLimits.h"

#include <cassert>
#include <cmath>

#define MAX_VELOCITY_IN_PERCENT_PER_SEC ((double)0.6)
#define ACCEL_RAMP_DURATION_IN_SECONDS ((double)0.35)
#define ACCEL_SETPOINT_IN_PERCENT_PER_SEC_SQUARED                                                  \
    (MAX_VELOCITY_IN_PERCENT_PER_SEC / ACCEL_RAMP_DURATION_IN_SECONDS)

Catcher::Catcher()
    : _positionInPercent(0.5f),
      _halfWidthInPercent(0.05f),
      _velocityInPercentPerSecond(0.0)
{
    assert(_halfWidthInPercent < 0.5f);
}

Catcher::~Catcher()
{
}

void Catcher::Update(double tickDurationInSeconds, bool moveLeft, bool moveRight)
{
    assert(tickDurationInSeconds > 0.0);

    MoveDirection requestedDirection = GetRequestedMoveDirection(moveLeft, moveRight);
    double velocityDelta = GetVelocityDelta(tickDurationInSeconds, requestedDirection);
    double newVelocity = GetNewVelocity(velocityDelta, requestedDirection);

    UpdatePositionAndVelocity(tickDurationInSeconds, newVelocity);
}

float Catcher::LeftEdgePosition()
{
    return LeftEdgeForPosition(_positionInPercent);
}

float Catcher::RightEdgePosition()
{
    return RightEdgeForPosition(_positionInPercent);
}

MoveDirection Catcher::GetRequestedMoveDirection(bool moveLeft, bool moveRight)
{
    bool both = moveLeft && moveRight;
    bool neither = !moveLeft && !moveRight;

    if (both || neither)
    {
        return _kNoMovement;
    }
    else if (moveLeft)
    {
        return _kMoveLeft;
    }
    else
    {
        return _kMoveRight;
    }
}

double Catcher::GetVelocityDelta(double tickDurationInSeconds, MoveDirection requestedDirection)
{
    double velocityDeltaMagnitude =
        tickDurationInSeconds * ACCEL_SETPOINT_IN_PERCENT_PER_SEC_SQUARED;

    if (requestedDirection == MoveDirection::_kNoMovement)
    {
        if (0.0f == _velocityInPercentPerSecond)
        {
            return 0.0;
        }
        else
        {
            // Velocity delta opposes current velocity
            return std::copysign(velocityDeltaMagnitude, -1.0f * _velocityInPercentPerSecond);
        }
    }
    else
    {
        // Velocity delta has the sign of the requested direction
        return std::copysign(velocityDeltaMagnitude, requestedDirection);
    }
}

double Catcher::GetNewVelocity(double velocityDeltaInPercentPerSecond,
                               MoveDirection requestedDirection)
{
    double newVelocityInPercentPerSecond =
        _velocityInPercentPerSecond + velocityDeltaInPercentPerSecond;

    // Clip to maximum velocity if new velocity was going to exceed it
    if (std::fabs(newVelocityInPercentPerSecond) > MAX_VELOCITY_IN_PERCENT_PER_SEC)
    {
        newVelocityInPercentPerSecond =
            std::copysign(MAX_VELOCITY_IN_PERCENT_PER_SEC, newVelocityInPercentPerSecond);
    }

    // Clip to zero velocity if new velocity was going to cross over zero for a no-movement request
    if ((requestedDirection == MoveDirection::_kNoMovement) &&
        (_velocityInPercentPerSecond * newVelocityInPercentPerSecond < 0.0))
    {
        newVelocityInPercentPerSecond = 0.0; // Catcher comes to a halt
    }

    return newVelocityInPercentPerSecond;
}

void Catcher::UpdatePositionAndVelocity(double tickDurationInSeconds, double newVelocity)
{
    // Use trapezoidal-rule to compute travel distance
    double averageVelocityInPercentPerSecond = (_velocityInPercentPerSecond + newVelocity) / 2.0;
    double travelDistanceInPercent = averageVelocityInPercentPerSecond * tickDurationInSeconds;

    float newPositionInPercent = _positionInPercent + (float)travelDistanceInPercent;

    if (LeftEdgeForPosition(newPositionInPercent) < LEFT_LIMIT_POSITION_IN_PERCENT)
    {
        newPositionInPercent = LEFT_LIMIT_POSITION_IN_PERCENT + _halfWidthInPercent;
        _velocityInPercentPerSecond = 0.0;
    }
    else if (RightEdgeForPosition(newPositionInPercent) > RIGHT_LIMIT_POSITION_IN_PERCENT)
    {
        newPositionInPercent = RIGHT_LIMIT_POSITION_IN_PERCENT - _halfWidthInPercent;
        _velocityInPercentPerSecond = 0.0;
    }
    else
    {
        _velocityInPercentPerSecond = newVelocity;
    }

    _positionInPercent = newPositionInPercent;
}

float Catcher::LeftEdgeForPosition(float position)
{
    return position - _halfWidthInPercent;
}

float Catcher::RightEdgeForPosition(float position)
{
    return position + _halfWidthInPercent;
}
