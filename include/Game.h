#ifndef CATCH_GAME_GAME_H
#define CATCH_GAME_GAME_H

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
    ~Game()
    {
    }

    void Resume();
    void Pause();
    void Update(GameInputs &inputs);
    bool IsPaused();

  private:
    bool _isPaused{true};
    unsigned int _points{0};
};

#endif
