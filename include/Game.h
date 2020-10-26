#ifndef CATCH_GAME_GAME_H
#define CATCH_GAME_GAME_H

#include "Catcher.h"
#include "Faller.h"

#include <cstdint>
#include <memory>
#include <vector>

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

    static std::shared_ptr<Game> CreateNewGame();

    void Resume();
    void Pause();
    void Update(double tickDurationInSeconds, GameInputs& inputs);
    bool IsPaused();

  private:
    void SetMyselfWeakPtr(std::shared_ptr<Game>& me);
    bool HasFallerBeenCaught(std::unique_ptr<Faller>& f);
    bool HasFallerFallenBeyondCaptureRegion(std::unique_ptr<Faller>& f);
    bool IsBetween(float position, float left, float right);

    Game(Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(Game&) = delete;
    Game& operator=(Game&&) = delete;

  private:
    std::weak_ptr<Game> _myself;
    bool _isPaused{true};
    uint32_t _points{0};
    std::unique_ptr<Catcher> _catcher;
    std::vector<std::unique_ptr<Faller>> _fallers;
    float _xGravityInPercentPerSecondSquared{0.0f};
    float _yGravityInPercentPerSecondSquared{0.0f};
};

#endif
