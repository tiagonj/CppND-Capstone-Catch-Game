#include "Application.h"
#include "InputReader.h"
#include "Rendering.h"

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

    _app.Initialise();
    _app.Run();
}

void Application::Initialise()
{
    Rendering::Initialise();
}

void Application::Run()
{
    while (true)
    {
        switch (_nextState)
        {
            case _kStartNewGame:
            {
                _app.CreateNewGame();
                _nextState = ApplicationState::_kPlay;
                break;
            }
            case _kPause:
            {
                _app.ExecutePauseLoop();
                break;
            }
            case _kPlay:
            {
                _app.ExecuteGameLoop();
                break;
            }
            case _kQuit:
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

    while (_nextState == ApplicationState::_kPlay)
    {
        auto autoMetronome = AutoMetronome(_gameMetronome);
        GameInputs gameInputs;
        _app.ProcessInputsWhenInGameLoop(gameInputs);
        double tickDurationInSeconds = 1.0 / _gameMetronome.UpdatesPerSecond();
        this->_game->Update(tickDurationInSeconds, gameInputs);
        Rendering::RenderGame();
    }

    _game->Pause();
}

void Application::ExecutePauseLoop()
{
    assert(_game->IsPaused());

    while (_nextState == ApplicationState::_kPause)
    {
        auto autoMetronome = AutoMetronome(_pauseMetronome);
        _app.ProcessInputsWhenInPauseLoop();
        // TODO render
    }
}

void Application::ProcessInputsWhenInGameLoop(GameInputs &gameInputs)
{
    ApplicationInputs appInputs;
    InputReader::ReadInputs(appInputs, gameInputs);

    if (appInputs.quitIsPressed)
    {
        _nextState = ApplicationState::_kQuit;
    }
    else if (appInputs.pauseIsPressed)
    {
        _nextState = ApplicationState::_kPause;
    }
}

void Application::ProcessInputsWhenInPauseLoop()
{
    ApplicationInputs appInputs;
    GameInputs gameInputsIgnored;
    InputReader::ReadInputs(appInputs, gameInputsIgnored);

    if (appInputs.quitIsPressed)
    {
        _nextState = ApplicationState::_kQuit;
    }
    else if (appInputs.pauseIsPressed)
    {
        _nextState = ApplicationState::_kPlay;
    }
}

int main()
{
    Application::Launch();
    return 0;
}
