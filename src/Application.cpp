#include "Application.h"
#include "Rendering.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

// Singleton application instance
Application Application::_app;

// Private constructor/destructor
Application::Application()
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
                // TODO
                break;
            }
            case _kPlay:
            {
                _app.PlayGame();
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

void Application::PlayGame()
{
    _game->Resume();

    long desiredFrameDurationInMs = 1000 / 60; // milliseconds per frame, at 60 frames per second

    while (_nextState == ApplicationState::_kPlay)
    {
        auto startTime = std::chrono::system_clock::now();
        // TODO: read inputs
        _game->Update();
        Rendering::RenderGame();
        auto endTime = std::chrono::system_clock::now();

        long executionDurationInMs =
            std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        if (executionDurationInMs < desiredFrameDurationInMs)
        {
            long sleepDurationInMs = desiredFrameDurationInMs - executionDurationInMs;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepDurationInMs));
        }
    }

    _game->Pause();
}

int main()
{
    Application::Launch();
    return 0;
}
