#include "Faller.h"
#include "PositionLimits.h"

#include <cassert>
#include <cmath>

Faller::~Faller()
{
}

void Faller::Update(double timeDeltaInSeconds, float xAccelInUnitsPerSecSquared,
                    float yAccelInUnitsPerSecSquared)
{
    UpdateXPosAndVel(timeDeltaInSeconds, xAccelInUnitsPerSecSquared);

    UpdatePosAndVel(timeDeltaInSeconds, _yPosition, _yVelocityInUnitsPerSecond,
                    yAccelInUnitsPerSecSquared);
}

float Faller::UpPosition() const
{
    return _yPosition + _halfHeight;
}

float Faller::DownPosition() const
{
    return _yPosition - _halfHeight;
}

float Faller::LeftPosition() const
{
    return _xPosition - _halfWidth;
}

float Faller::RightPosition() const
{
    return _xPosition + _halfWidth;
}

uint32_t Faller::RewardPoints() const
{
    return _rewardPoints;
}

Faller::Faller(float width, float height, float x, float vx, float vy, uint32_t rewardPoints)
    : _xPosition(x),
      _yPosition(UP_LIMIT_POSITION - (height / 2.0f)),
      _xVelocityInUnitsPerSecond(vx),
      _yVelocityInUnitsPerSecond(vy),
      _rewardPoints(rewardPoints),
      _halfWidth(width / 2.0f),
      _halfHeight(height / 2.0f)
{
    assert(_xPosition >= 0.0);
    assert(_xPosition <= 1.0);

    float lowerLimit = LEFT_LIMIT_POSITION + _halfWidth;
    float upperLimit = RIGHT_LIMIT_POSITION - _halfWidth;

    _xPosition = std::max(_xPosition, lowerLimit);
    _xPosition = std::min(_xPosition, upperLimit);
}

void Faller::UpdatePosAndVel(double timeDeltaInSeconds, float& pos, float& vel, float accel)
{
    double timeDeltaSquared = std::pow(timeDeltaInSeconds, 2.0);
    pos = pos + (vel * timeDeltaInSeconds) + (0.5 * accel * timeDeltaSquared);
    vel = vel + (accel * timeDeltaInSeconds);
}

void Faller::UpdateXPosAndVel(double timeDeltaInSeconds, float accel)
{
    float _xPrevPosition = _xPosition;
    float _xPrevVelocity = _xVelocityInUnitsPerSecond;

    UpdatePosAndVel(timeDeltaInSeconds, _xPosition, _xVelocityInUnitsPerSecond, accel);

    bool exceedsLeftLimitPos = (_xPosition < LEFT_LIMIT_POSITION);
    bool exceedsRightLimitPos = (_xPosition > RIGHT_LIMIT_POSITION);

    if (exceedsLeftLimitPos || exceedsRightLimitPos)
    {
        // Revert
        _xPosition = _xPrevPosition;
        _xVelocityInUnitsPerSecond = _xPrevVelocity;

        float limitPos = exceedsLeftLimitPos ? LEFT_LIMIT_POSITION : RIGHT_LIMIT_POSITION;

        // Solve quadratic equation: at which point in time is the limit position reached?
        float a = accel / 2.0f;
        float b = _xVelocityInUnitsPerSecond;
        float c = _xPosition - limitPos;
        float smallest;
        float largest;
        SolveQuadraticEq(a, b, c, smallest, largest);

        // Pick largest solution if it's within the total time delta, otherwise pick the smallest
        float t = (largest <= timeDeltaInSeconds) ? largest : smallest;
        assert(t > 0.0f);
        float remainingTime = timeDeltaInSeconds - t;

        // Jump to the intermediate solution
        _xPosition = limitPos;
        _xVelocityInUnitsPerSecond *= -1.0f;

        // Re-enter to calculate remaining solution (Note: because of the const accel and quadratic
        // nature of the motion equation we are guaranteed only do have to do this at most once
        UpdateXPosAndVel(remainingTime, accel);
    }
}

void Faller::SolveQuadraticEq(float a, float b, float c, float& smallestSolution,
                              float& largestSolution)
{
    // We're expecting real solutions only
    float discriminant = std::pow(b, 2.0f) - (4.0f * a * c);
    assert(discriminant >= 0.0f); // TODO make this slightly more tolerant

    float sqrtOfDiscriminant = std::sqrt(discriminant);
    float denominator = 2 * a;

    float s1 = (-b - sqrtOfDiscriminant) / denominator;
    float s2 = (-b + sqrtOfDiscriminant) / denominator;

    smallestSolution = std::min(s1, s2);
    largestSolution = std::max(s1, s2);
}
