#include "FallerFactory.h"

#include <cassert>
#include <chrono>
#include <thread>

#define PAUSE_SLEEP_DURATION_IN_MS (10)

FallerFactory::FallerFactory(double generationProbabilty, uint32_t updatePeriodInMs,
                             float maxVerticalVelocityMagnitude, std::weak_ptr<FallerQueue>& queue)
    : _nextState(FallerFactoryState::_kPause), // Purposely start in the paused state
      _activationThresholdPercentage(1.0 - generationProbabilty),
      _updatePeriodInMilliseconds(updatePeriodInMs),
      _maxVerticalVelocityMagnitude(maxVerticalVelocityMagnitude),
      _fallerQueue(queue)
{
    assert(_activationThresholdPercentage > 0.0);
    assert(_activationThresholdPercentage < 1.0);
    assert(_maxVerticalVelocityMagnitude > 0.0f);

    std::random_device rd;
    _generationEngine.seed(rd());
    _horizontalPositionEngine.seed(rd());
    _verticalVelocityEngine.seed(rd());
}

void FallerFactory::Run()
{
    while (!IsNextState(FallerFactoryState::_kTerminate))
    {
        if (IsNextState(FallerFactoryState::_kPause))
        {
            Sleep(PAUSE_SLEEP_DURATION_IN_MS);
        }
        else
        {
            // Generate and add new Faller to the game based
            // on simple probabilty thresholding logic
            std::uniform_real_distribution<> dist(0.0, 1.0);
            if (dist(_generationEngine) > _activationThresholdPercentage)
            {
                AddFallerToGame();
            }

            Sleep(_updatePeriodInMilliseconds);
        }
    }
}

void FallerFactory::Pause()
{
    std::lock_guard<std::mutex> lock(_nextStateMutex);
    assert(IsNextState(FallerFactoryState::_kRun));
    _nextState = FallerFactoryState::_kPause;
}

void FallerFactory::Resume()
{
    std::lock_guard<std::mutex> lock(_nextStateMutex);
    assert(IsNextState(FallerFactoryState::_kPause));
    _nextState = FallerFactoryState::_kRun;
}

void FallerFactory::Terminate()
{
    std::lock_guard<std::mutex> lock(_nextStateMutex);
    assert(!IsNextState(FallerFactoryState::_kTerminate));
    _nextState = FallerFactoryState::_kTerminate;
}

bool FallerFactory::IsNextState(FallerFactoryState state)
{
    std::lock_guard<std::mutex> lock(_nextStateMutex);
    return state == _nextState;
}

void FallerFactory::Sleep(uint32_t sleepDurationInMilliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepDurationInMilliseconds));
}

void FallerFactory::AddFallerToGame()
{
    float x = GenerateHorizontalPosition();
    float vy = GenerateVerticalVelocity();

    // Get a shared_ptr to manipulate the faller queue. Note that this operation *must* succeed
    // because the Factory is deleted before Game (who is the original owner of the shared_ptr)
    std::shared_ptr<FallerQueue> queue = _fallerQueue.lock();
    assert(queue);

    queue->Push(std::move(CreateFaller(x, vy)));
}

float FallerFactory::GenerateHorizontalPosition()
{
    std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(_horizontalPositionEngine);
}

float FallerFactory::GenerateVerticalVelocity()
{
    std::uniform_real_distribution<> dist(-_maxVerticalVelocityMagnitude, 0.0);
    return dist(_verticalVelocityEngine);
}
