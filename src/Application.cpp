#include "Application.h"
#include "Rendering.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <thread>

// Singleton application instance
Application Application::_app;

// Private constructor/destructor
Application::Application() : _gameMetronome(30, 120)
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
        // TODO: read inputs
        this->_game->Update();
        Rendering::RenderGame();
    }

    _game->Pause();
}

void Application::ExecutePauseLoop()
{
    assert(_game->IsPaused());

    while (_nextState == ApplicationState::_kPause)
    {
        // TODO: read inputs
    }
}

int main()
{
    Application::Launch();
    return 0;
}
