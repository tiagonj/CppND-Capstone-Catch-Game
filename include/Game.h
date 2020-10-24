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

  private:
    // TODO
};

#endif
