#ifndef CATCH_GAME_GAME_H
#define CATCH_GAME_GAME_H

#include "Catcher.h"
#include "Faller.h"
#include "FallerGenerator.h"
#include "FallerQueue.h"

#include <cstdint>
#include <list>
#include <memory>
#include <mutex>

struct GameInputs
{
    bool moveLeftIsPressed;
    bool moveRightIsPressed;
};

class Game
{
  public:
    Game();
    ~Game();

    void Resume();
    void Pause();
    void Update(double tickDurationInSeconds, GameInputs& inputs);
    bool IsPaused() const;

    // State
    uint32_t Points() const;
    std::size_t NumberOfFallers() const;
    float CatcherLeftEdgePositionInPercent() const;
    float CatcherRightEdgePositionInPercent() const;

  private:
    bool HasFallerBeenCaught(std::unique_ptr<Faller>& f);
    bool HasFallerFallenBeyondCaptureRegion(std::unique_ptr<Faller>& f);
    bool IsBetween(float position, float left, float right);

    Game(Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&) = delete;
    Game& operator=(Game&&) = delete;

  private:
    bool _isPaused{true};
    uint32_t _points{0};
    std::unique_ptr<Catcher> _catcher;
    std::shared_ptr<FallerQueue> _fallerQueue;
    std::unique_ptr<FallerGenerator> _generator;
    std::list<std::unique_ptr<Faller>> _fallers;
    float _xGravityInPercentPerSecondSquared{0.0f};
    float _yGravityInPercentPerSecondSquared{0.0f};
};

#endif
