#ifndef CATCH_GAME_GAME_APPLICATION_H
#define CATCH_GAME_GAME_APPLICATION_H

#include "Game.h"

#include <memory>

class GameApplication
{
  public:
    static void Launch();

  private:
    GameApplication()
    {
    }
    ~GameApplication()
    {
    }

    void CreateNewGame();
    void PlayGame();

  private:
    static GameApplication _app;
    std::unique_ptr<Game> _game;
};

#endif
