#ifndef CATCH_GAME_GAME_H
#define CATCH_GAME_GAME_H

#include <memory>

class Game
{
  public:
    Game();
    ~Game()
    {
    }

    void Resume();
    void Pause();
    void Update();
    bool IsPaused();

  private:
    bool _isPaused{true};
    unsigned int _points{0};
};

#endif
