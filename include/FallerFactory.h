#ifndef CATCH_GAME_FALLER_FACTORY_H
#define CATCH_GAME_FALLER_FACTORY_H

#include "Faller.h"
#include "FallerQueue.h"

#include <cstdint>
#include <memory>
#include <mutex>
#include <random>

enum FallerFactoryState
{
    _kPause = 0,
    _kRun,
    _kTerminate
};

// Interface class for factories of Faller objects
class FallerFactory
{
  public:
    FallerFactory(double generationProbabilty, uint32_t updatePeriodInMs,
                  float maxVerticalVelocityMagnitude, std::weak_ptr<FallerQueue>& queue);
    ~FallerFactory();
    void Run();
    void Pause();
    void Resume();
    void Terminate();

  protected:
    virtual std::unique_ptr<Faller> CreateFaller(float x, float vy) = 0;

  private:
    bool IsNextState(FallerFactoryState state);
    void Sleep(uint32_t sleepDurationInMilliseconds);
    void AddFallerToGame();
    float GenerateHorizontalPosition();
    float GenerateVerticalVelocity();

    FallerFactory() = delete;
    FallerFactory(FallerFactory&) = delete;
    FallerFactory(FallerFactory&&) = delete;
    FallerFactory& operator=(FallerFactory&) = delete;
    FallerFactory& operator=(FallerFactory&&) = delete;

  private:
    std::mutex _nextStateMutex;
    FallerFactoryState _nextState;
    std::mt19937 _generationEngine;
    std::mt19937 _horizontalPositionEngine;
    std::mt19937 _verticalVelocityEngine;
    double _activationThresholdPercentage;
    uint32_t _updatePeriodInMilliseconds{0U};
    float _maxVerticalVelocityMagnitude;
    std::weak_ptr<FallerQueue> _fallerQueue;
};

#endif
