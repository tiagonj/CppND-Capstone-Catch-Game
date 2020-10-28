#include "Game.h"
#include "PositionLimits.h"

#include <algorithm>
#include <cassert>

#define DEFAULT_X_GRAVITY_IN_PERCENT_PER_SEC_SQUARED ((float)0.0f)
#define DEFAULT_Y_GRAVITY_IN_PERCENT_PER_SEC_SQUARED ((float)-0.1f)
#define FALLER_ESCAPE_HEIGHT_THRESHOLD_PERCENT ((float)0.15f)
#define FALLER_CAPTURE_WIDTH_THRESHOLD_PERCENT ((float)0.25f)

Game::Game()
    : _isPaused(true), // The game is purposely created in paused state
      _points(0),
      _xGravityInPercentPerSecondSquared(DEFAULT_X_GRAVITY_IN_PERCENT_PER_SEC_SQUARED),
      _yGravityInPercentPerSecondSquared(DEFAULT_Y_GRAVITY_IN_PERCENT_PER_SEC_SQUARED)
{
    assert(_yGravityInPercentPerSecondSquared < 0.0f);

    _catcher = std::make_unique<Catcher>();
    _fallerQueue = std::make_shared<FallerQueue>();
    _generator = std::make_unique<FallerGenerator>(_fallerQueue);
}

Game::~Game()
{
}

void Game::Resume()
{
    assert(IsPaused());
    _generator->Resume();
    _isPaused = false;
}

void Game::Pause()
{
    assert(!IsPaused());
    _generator->Pause();
    _isPaused = true;
}

void Game::Update(double tickDurationInSeconds, GameInputs& inputs)
{
    assert(!IsPaused());

    // Update position and velocity of the catcher
    _catcher->Update(tickDurationInSeconds, inputs.moveLeftIsPressed, inputs.moveRightIsPressed);

    // Accept any fallers that have been staged since the last execution
    _fallerQueue->PopAll(_fallers);

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
}

bool Game::IsPaused() const
{
    return _isPaused;
}

uint32_t Game::Points() const
{
    return _points;
}

std::size_t Game::NumberOfFallers() const
{
    return _fallers.size();
}

float Game::CatcherLeftEdgePositionInPercent() const
{
    return _catcher->LeftEdgePosition();
}

float Game::CatcherRightEdgePositionInPercent() const
{
    return _catcher->RightEdgePosition();
}

bool Game::HasFallerBeenCaught(std::unique_ptr<Faller>& f)
{
    if ((f->DownPosition() <= DOWN_LIMIT_POSITION) && !HasFallerFallenBeyondCaptureRegion(f))
    {
        float leftPos = f->LeftPosition();
        float rightPos = f->RightPosition();
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

bool Game::HasFallerFallenBeyondCaptureRegion(std::unique_ptr<Faller>& f)
{
    float upPos = f->UpPosition();
    float dnPos = f->DownPosition();
    assert(dnPos < upPos);

    if (upPos < DOWN_LIMIT_POSITION)
    {
        return true;
    }
    else if (dnPos < DOWN_LIMIT_POSITION)
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
