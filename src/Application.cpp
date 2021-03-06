#include "Application.h"
#include "InputReader.h"
#include "Renderer.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <thread>

// Singleton application instance
Application Application::_app;

// Private constructor/destructor
Application::Application() : _gameMetronome(30, 120), _pauseMetronome(30, 120)
{
}

Application::~Application()
{
}

void Application::Launch()
{
    std::cout << "Welcome to Catch!"
              << "\n";

    if (_app.Initialise())
    {
        _app.Run();

        std::cout << "Exiting... Hope you enjoyed playing Catch!"
                  << "\n";
    }
}

bool Application::Initialise()
{
    _renderer = std::make_unique<Renderer>("Catch!");

    return _renderer->InitialisedSuccessfully();
}

void Application::Run()
{

    while (true)
    {
        switch (_nextState)
        {
            case _kStartNewGame:
            {
                CreateNewGame();
                _nextState = ApplicationState::_kPlayGame;
                break;
            }
            case _kPauseGame:
            {
                ExecutePauseLoop();
                break;
            }
            case _kPlayGame:
            {
                ExecuteGameLoop();
                break;
            }
            case _kQuitApplication:
            {
                return;
            }
            default:
            {
                throw "Unknown Application state!";
            }
        }
    }
}

void Application::CreateNewGame()
{
    _game = std::make_unique<Game>();
}

void Application::ExecuteGameLoop()
{
    _game->Resume();

    while (_nextState == ApplicationState::_kPlayGame)
    {
        auto autoMetronome = AutoMetronome(_gameMetronome);
        GameInputs gameInputs;
        ProcessInputsWhenInGameLoop(gameInputs);
        double tickDurationInSeconds = 1.0 / _gameMetronome.UpdatesPerSecond();
        this->_game->Update(tickDurationInSeconds, gameInputs);
        _renderer->RenderGame(*_game.get(), _gameMetronome.UpdatesPerSecond());
    }

    _game->Pause();
}

void Application::ExecutePauseLoop()
{
    assert(_game->IsPaused());

    while (_nextState == ApplicationState::_kPauseGame)
    {
        auto autoMetronome = AutoMetronome(_pauseMetronome);
        ProcessInputsWhenInPauseLoop();
        _renderer->RenderGame(*_game.get(), _gameMetronome.UpdatesPerSecond());
    }
}

void Application::ProcessInputsWhenInGameLoop(GameInputs& gameInputs)
{
    ApplicationInputs appInputs;
    InputReader::ReadInputs(appInputs, gameInputs, *_renderer.get());

    if (appInputs.quitIsPressed)
    {
        _nextState = ApplicationState::_kQuitApplication;
    }
    else if (appInputs.pauseIsPressed)
    {
        _nextState = ApplicationState::_kPauseGame;
    }
}

void Application::ProcessInputsWhenInPauseLoop()
{
    ApplicationInputs appInputs;
    GameInputs gameInputsIgnored;
    InputReader::ReadInputs(appInputs, gameInputsIgnored, *_renderer.get());

    if (appInputs.quitIsPressed)
    {
        _nextState = ApplicationState::_kQuitApplication;
    }
    else if (appInputs.pauseIsPressed)
    {
        _nextState = ApplicationState::_kPlayGame;
    }
}

int main()
{
    Application::Launch();
    return 0;
}
