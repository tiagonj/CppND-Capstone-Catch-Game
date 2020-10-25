#include "Game.h"
#include "PositionLimits.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#define DEFAULT_X_GRAVITY_IN_PERCENT_PER_SEC_SQUARED ((float)0.0f)
#define DEFAULT_Y_GRAVITY_IN_PERCENT_PER_SEC_SQUARED ((float)0.01f)
#define FALLER_ESCAPE_HEIGHT_THRESHOLD_PERCENT ((float)0.15f)
#define FALLER_CAPTURE_WIDTH_THRESHOLD_PERCENT ((float)0.25f)

Game::Game()
    : _isPaused(true),
      _points(0),
      _xGravityInPercentPerSecondSquared(DEFAULT_X_GRAVITY_IN_PERCENT_PER_SEC_SQUARED),
      _yGravityInPercentPerSecondSquared(DEFAULT_Y_GRAVITY_IN_PERCENT_PER_SEC_SQUARED)
{
    _catcher = std::make_unique<Catcher>();
}

Game::~Game()
{
}

void Game::Resume()
{
    assert(IsPaused());
    // TODO
    _isPaused = false;
}

void Game::Pause()
{
    assert(!IsPaused());
    // TODO
    _isPaused = true;
}

void Game::Update(double tickDurationInSeconds, GameInputs &inputs)
{
    assert(!IsPaused());

    // Update position and velocity of the catcher
    _catcher->Update(tickDurationInSeconds, inputs.moveLeftIsPressed, inputs.moveRightIsPressed);

    for (auto it = _fallers.begin(); it != _fallers.end();)
    {
        // Update position and velocity of each faller object
        (*it)->Update(tickDurationInSeconds, _xGravityInPercentPerSecondSquared,
                      _yGravityInPercentPerSecondSquared);

        if (HasFallerFallenBeyondCaptureRegion(*it))
        {
            it = _fallers.erase(it); // Remove from vector of fallers
        }
        else if (HasFallerBeenCaught(*it))
        {
            _points += (*it)->RewardPoints(); // Accrue points
            it = _fallers.erase(it);          // Remove from vector of fallers
        }
        else
        {
            it = std::next(it);
        }
    }

    for (unsigned int ii = 0; ii < 4294967295; ++ii)
    {
        // Do nothing
        (void)inputs;
    }

    std::cout << "Finished updating game! tickDuration = " << tickDurationInSeconds
              << ", updates/sec = " << (1.0 / tickDurationInSeconds) << "\n";
}

bool Game::IsPaused()
{
    return _isPaused;
}

bool Game::HasFallerBeenCaught(std::unique_ptr<Faller> &f)
{
    if ((f->DownPositionInPercent() <= DOWN_LIMIT_POSITION_IN_PERCENT) &&
        !HasFallerFallenBeyondCaptureRegion(f))
    {
        float leftPos = f->LeftPositionInPercent();
        float rightPos = f->RightPositionInPercent();
        float width = rightPos - leftPos;

        float catcherLeftPos = _catcher->LeftEdgePosition();
        float catcherRightPos = _catcher->RightEdgePosition();

        bool leftIsBetween = IsBetween(leftPos, catcherLeftPos, catcherRightPos);
        bool rightIsBetween = IsBetween(rightPos, catcherLeftPos, catcherRightPos);

        if (leftIsBetween && rightIsBetween)
        {
            return true;
        }
        else if (leftIsBetween)
        {
            float overlap = catcherRightPos - leftPos;
            assert(overlap >= 0.0f);
            return overlap >= (FALLER_CAPTURE_WIDTH_THRESHOLD_PERCENT * width);
        }
        else if (rightIsBetween)
        {
            float overlap = rightPos - catcherLeftPos;
            assert(overlap >= 0.0f);
            return overlap >= (FALLER_CAPTURE_WIDTH_THRESHOLD_PERCENT * width);
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool Game::HasFallerFallenBeyondCaptureRegion(std::unique_ptr<Faller> &f)
{
    float upPos = f->UpPositionInPercent();
    float dnPos = f->DownPositionInPercent();
    assert(dnPos < upPos);

    if (upPos < DOWN_LIMIT_POSITION_IN_PERCENT)
    {
        return true;
    }
    else if (dnPos < DOWN_LIMIT_POSITION_IN_PERCENT)
    {
        float height = upPos - dnPos;
        return upPos < (FALLER_ESCAPE_HEIGHT_THRESHOLD_PERCENT * height);
    }

    return false;
}

bool Game::IsBetween(float position, float left, float right)
{
    assert(left < right);
    return (position >= left) && (position <= right);
}
