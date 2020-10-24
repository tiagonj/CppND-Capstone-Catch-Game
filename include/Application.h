#ifndef CATCH_GAME_GAME_APPLICATION_H
#define CATCH_GAME_GAME_APPLICATION_H

#include "Game.h"
#include "Metronome.h"

#include <memory>

struct ApplicationInputs
{
    bool pauseIsPressed;
    bool quitIsPressed;
};

enum ApplicationState
{
    _kStartNewGame = 0,
    _kPause,
    _kPlay,
    _kQuit
};

class Application
{
  public:
    static void Launch();

  private:
    Application();
    ~Application();

    void Initialise();
    void Run();

    void CreateNewGame();
    void ExecuteGameLoop();
    void ExecutePauseLoop();
    void ProcessInputsWhenInGameLoop(GameInputs &gameInputs);
    void ProcessInputsWhenInPauseLoop();

  private:
    static Application _app; // Singleton application instance

    std::unique_ptr<Game> _game;
    ApplicationState _nextState{ApplicationState::_kStartNewGame};
    Metronome _gameMetronome;
    Metronome _pauseMetronome;
};

#endif
