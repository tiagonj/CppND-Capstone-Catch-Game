#include "Faller.h"
#include "PositionLimits.h"

#include <cassert>
#include <cmath>

Faller::~Faller()
{
}

void Faller::Update(double timeDeltaInSeconds, float xAccelInPercentPerSecSquared,
                    float yAccelInPercentPerSecSquared)
{
    UpdateXPosAndVel(timeDeltaInSeconds, xAccelInPercentPerSecSquared);

    UpdatePosAndVel(timeDeltaInSeconds, _yPositionInPercent, _yVelocityInPercentPerSecond,
                    yAccelInPercentPerSecSquared);
}

ImageArtifact& Faller::GetImageArtifact() const
{
    return *_img;
}

float Faller::UpPositionInPercent() const
{
    return _yPositionInPercent + _img->HalfHeightInPercent();
}

float Faller::DownPositionInPercent() const
{
    return _yPositionInPercent - _img->HalfHeightInPercent();
}

float Faller::LeftPositionInPercent() const
{
    return _xPositionInPercent - _img->HalfWidthInPercent();
}

float Faller::RightPositionInPercent() const
{
    return _xPositionInPercent + _img->HalfWidthInPercent();
}

uint32_t Faller::RewardPoints() const
{
    return _rewardPoints;
}

Faller::Faller(std::shared_ptr<ImageArtifact>& img, float x, float vx, float vy,
               uint32_t rewardPoints)
    : _xPositionInPercent(x),
      _yPositionInPercent(UP_LIMIT_POSITION_IN_PERCENT - img->HalfHeightInPercent()),
      _xVelocityInPercentPerSecond(vx),
      _yVelocityInPercentPerSecond(vy),
      _rewardPoints(rewardPoints),
      _img(img) // Copy constructor => share ownership of the image artifact
{
    assert(_xPositionInPercent >= 0.0);
    assert(_xPositionInPercent <= 1.0);

    float halfWidthInPercent = _img->HalfWidthInPercent();
    float lowerLimit = LEFT_LIMIT_POSITION_IN_PERCENT + halfWidthInPercent;
    float upperLimit = RIGHT_LIMIT_POSITION_IN_PERCENT - halfWidthInPercent;

    _xPositionInPercent = std::max(_xPositionInPercent, lowerLimit);
    _xPositionInPercent = std::min(_xPositionInPercent, upperLimit);
}

void Faller::UpdatePosAndVel(double timeDeltaInSeconds, float& pos, float& vel, float accel)
{
    double timeDeltaSquared = std::pow(timeDeltaInSeconds, 2.0);
    pos = pos + (vel * timeDeltaInSeconds) + (0.5 * accel * timeDeltaSquared);
    vel = vel + (accel * timeDeltaInSeconds);
}

void Faller::UpdateXPosAndVel(double timeDeltaInSeconds, float accel)
{
    float _xPrevPosition = _xPositionInPercent;
    float _xPrevVelocity = _xVelocityInPercentPerSecond;

    UpdatePosAndVel(timeDeltaInSeconds, _xPositionInPercent, _xVelocityInPercentPerSecond, accel);

    bool exceedsLeftLimitPos = (_xPositionInPercent < LEFT_LIMIT_POSITION_IN_PERCENT);
    bool exceedsRightLimitPos = (_xPositionInPercent > RIGHT_LIMIT_POSITION_IN_PERCENT);

    if (exceedsLeftLimitPos || exceedsRightLimitPos)
    {
        // Revert
        _xPositionInPercent = _xPrevPosition;
        _xVelocityInPercentPerSecond = _xPrevVelocity;

        float limitPos =
            exceedsLeftLimitPos ? LEFT_LIMIT_POSITION_IN_PERCENT : RIGHT_LIMIT_POSITION_IN_PERCENT;

        // Solve quadratic equation: at which point in time is the limit position reached?
        float a = accel / 2.0f;
        float b = _xVelocityInPercentPerSecond;
        float c = _xPositionInPercent - limitPos;
        float smallest;
        float largest;
        SolveQuadraticEq(a, b, c, smallest, largest);

        // Pick largest solution if it's within the total time delta, otherwise pick the smallest
        float t = (largest <= timeDeltaInSeconds) ? largest : smallest;
        assert(t > 0.0f);
        float remainingTime = timeDeltaInSeconds - t;

        // Jump to the intermediate solution
        _xPositionInPercent = limitPos;
        _xVelocityInPercentPerSecond *= -1.0f;

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
