#include "Catcher.h"
#include "PositionLimits.h"

#include <cassert>
#include <cmath>

#define MAX_VELOCITY_IN_UNITS_PER_SEC ((double)0.6)
#define ACCEL_RAMP_DURATION_IN_SECONDS ((double)0.35)
#define ACCEL_SETPOINT_IN_UNITS_PER_SEC_SQUARED                                                    \
    (MAX_VELOCITY_IN_UNITS_PER_SEC / ACCEL_RAMP_DURATION_IN_SECONDS)

Catcher::Catcher() : _centrePosition(0.5f), _halfWidth(0.05f), _velocityInUnitsPerSecond(0.0)
{
    assert(_halfWidth < 0.5f);
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
    return LeftEdgeForCentrePosition(_centrePosition);
}

float Catcher::RightEdgePosition()
{
    return RightEdgeForCentrePosition(_centrePosition);
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
    double velocityDeltaMagnitude = tickDurationInSeconds * ACCEL_SETPOINT_IN_UNITS_PER_SEC_SQUARED;

    if (requestedDirection == MoveDirection::_kNoMovement)
    {
        if (0.0f == _velocityInUnitsPerSecond)
        {
            return 0.0;
        }
        else
        {
            // Velocity delta opposes current velocity
            return std::copysign(velocityDeltaMagnitude, -1.0f * _velocityInUnitsPerSecond);
        }
    }
    else
    {
        // Velocity delta has the sign of the requested direction
        return std::copysign(velocityDeltaMagnitude, requestedDirection);
    }
}

double Catcher::GetNewVelocity(double velocityDeltaInUnitsPerSecond,
                               MoveDirection requestedDirection)
{
    double newVelocityInUnitsPerSecond = _velocityInUnitsPerSecond + velocityDeltaInUnitsPerSecond;

    // Clip to maximum velocity if new velocity was going to exceed it
    if (std::fabs(newVelocityInUnitsPerSecond) > MAX_VELOCITY_IN_UNITS_PER_SEC)
    {
        newVelocityInUnitsPerSecond =
            std::copysign(MAX_VELOCITY_IN_UNITS_PER_SEC, newVelocityInUnitsPerSecond);
    }

    // Clip to zero velocity if new velocity was going to cross over zero for a no-movement request
    if ((requestedDirection == MoveDirection::_kNoMovement) &&
        (_velocityInUnitsPerSecond * newVelocityInUnitsPerSecond < 0.0))
    {
        newVelocityInUnitsPerSecond = 0.0; // Catcher comes to a halt
    }

    return newVelocityInUnitsPerSecond;
}

void Catcher::UpdatePositionAndVelocity(double tickDurationInSeconds, double newVelocity)
{
    // Use trapezoidal-rule to compute travel distance
    double averageVelocityInUnitsPerSecond = (_velocityInUnitsPerSecond + newVelocity) / 2.0;
    double travelDistanceInPercent = averageVelocityInUnitsPerSecond * tickDurationInSeconds;

    float newCentrePosition = _centrePosition + (float)travelDistanceInPercent;

    if (LeftEdgeForCentrePosition(newCentrePosition) < LEFT_LIMIT_POSITION)
    {
        newCentrePosition = LEFT_LIMIT_POSITION + _halfWidth;
        _velocityInUnitsPerSecond = 0.0;
    }
    else if (RightEdgeForCentrePosition(newCentrePosition) > RIGHT_LIMIT_POSITION)
    {
        newCentrePosition = RIGHT_LIMIT_POSITION - _halfWidth;
        _velocityInUnitsPerSecond = 0.0;
    }
    else
    {
        _velocityInUnitsPerSecond = newVelocity;
    }

    _centrePosition = newCentrePosition;
}

float Catcher::LeftEdgeForCentrePosition(float centrePosition)
{
    return centrePosition - _halfWidth;
}

float Catcher::RightEdgeForCentrePosition(float centrePosition)
{
    return centrePosition + _halfWidth;
}
