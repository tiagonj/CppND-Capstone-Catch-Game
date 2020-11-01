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
    bool exceedsLeftLimitPos = true;
    bool exceedsRightLimitPos = true;

    AttemptXNaiveIntegration(timeDeltaInSeconds, accel, exceedsLeftLimitPos, exceedsRightLimitPos);

    if (exceedsLeftLimitPos || exceedsRightLimitPos)
    {
        float limitPos = exceedsLeftLimitPos ? LEFT_LIMIT_POSITION : RIGHT_LIMIT_POSITION;
        float pos = exceedsLeftLimitPos ? LeftPosition() : RightPosition();

        double bounceTimeDelta = GetBounceTimeDelta(timeDeltaInSeconds, pos, limitPos,
                                                    _xVelocityInUnitsPerSecond, accel);
        double remainingTime = timeDeltaInSeconds - bounceTimeDelta;

        // Jump to 'bounceTimeDelta' i.e. instant the bounce occurs
        _xPosition = exceedsLeftLimitPos ? (limitPos + _halfWidth) : (limitPos - _halfWidth);
        _xVelocityInUnitsPerSecond *= -1.0f; // Bounce off (perfectly elastic, i.e. no energy loss)

        // Attempt to integrate for the remaining duration
        bool exceedsLeftLimitPosAgain = true;
        bool exceedsRightLimitPosAgain = true;
        AttemptXNaiveIntegration(remainingTime, accel, exceedsLeftLimitPosAgain,
                                 exceedsRightLimitPosAgain);

        if (exceedsRightLimitPosAgain || exceedsRightLimitPosAgain)
        {
            // Assert consistency with original exceedence
            // (would be weird if the opposite limit was being exceeded now)
            assert(exceedsLeftLimitPos == exceedsLeftLimitPosAgain);
            assert(exceedsRightLimitPos == exceedsRightLimitPosAgain);

            // If the solution exceeds the limits again then the velocity is not strong enough to
            // overcome the acceleration; Null velocity altogether
            _xVelocityInUnitsPerSecond = 0.0f;
        }
    }
}

void Faller::AttemptXNaiveIntegration(double timeDeltaInSeconds, float accel,
                                      bool& exceedsLeftLimitPos, bool& exceedsRightLimitPos)
{
    float _xPrevPosition = _xPosition;
    float _xPrevVelocity = _xVelocityInUnitsPerSecond;

    // Try naive integration (may result in left/right bounds exceedance)
    UpdatePosAndVel(timeDeltaInSeconds, _xPosition, _xVelocityInUnitsPerSecond, accel);

    exceedsLeftLimitPos = (LeftPosition() < LEFT_LIMIT_POSITION);
    exceedsRightLimitPos = (RightPosition() > RIGHT_LIMIT_POSITION);

    if (exceedsLeftLimitPos || exceedsRightLimitPos)
    {
        // Revert to values prior to naive integration attempt
        _xPosition = _xPrevPosition;
        _xVelocityInUnitsPerSecond = _xPrevVelocity;
    }
}

double Faller::GetBounceTimeDelta(double intervalInSeconds, float position, float limitPosition,
                                  float velocity, float accel)
{
    // Solve quadratic equation: at which point in time is the limit position reached?
    double a = accel / 2.0f;
    double b = velocity;
    double c = position - limitPosition;
    double smallest;
    double largest;
    SolveQuadraticEq(a, b, c, smallest, largest);

    // Pick largest solution if it's within the total time delta, otherwise pick the smallest
    double bounceTime = (largest <= intervalInSeconds) ? largest : smallest;
    assert(bounceTime >= 0.0);
    return bounceTime;
}

void Faller::SolveQuadraticEq(double a, double b, double c, double& smallestSolution,
                              double& largestSolution)
{
    assert(a != 0.0f);

    // We're expecting real solutions only
    double discriminant = std::pow(b, 2.0) - (4.0 * a * c);
    assert(discriminant >= -1e-4);

    double sqrtOfDiscriminant = std::sqrt(discriminant);
    double denominator = 2.0 * a;

    double s1 = (-b - sqrtOfDiscriminant) / denominator;
    double s2 = (-b + sqrtOfDiscriminant) / denominator;

    smallestSolution = std::min(s1, s2);
    largestSolution = std::max(s1, s2);
}
