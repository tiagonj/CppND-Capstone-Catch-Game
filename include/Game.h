#ifndef CATCH_GAME_GAME_H
#define CATCH_GAME_GAME_H

#include "Catcher.h"

#include <cstdint>
#include <memory>

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
    void Update(double tickDurationInSeconds, GameInputs &inputs);
    bool IsPaused();

  private:
    Game(Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game &) = delete;
    Game &operator=(Game &&) = delete;

  private:
    bool _isPaused{true};
    uint32_t _points{0};
    std::unique_ptr<Catcher> _catcher;
};

#endif
