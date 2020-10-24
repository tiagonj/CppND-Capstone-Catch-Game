#ifndef CATCH_GAME_GAME_APPLICATION_H
#define CATCH_GAME_GAME_APPLICATION_H

#include "Game.h"

#include <memory>

class Application
{
  public:
    static void Launch();

  private:
    Application()
    {
    }
    ~Application()
    {
    }

    void CreateNewGame();
    void PlayGame();

  private:
    static Application _app;
    std::unique_ptr<Game> _game;
};

#endif
