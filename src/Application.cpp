#include "Application.h"
#include "Rendering.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

Application Application::_app;

void Application::Launch()
{
    std::cout << "Welcome to Catch!"
              << "\n";

    Rendering::Initialise();

    _app.CreateNewGame();
    _app.PlayGame();

    // TODO handle PauseGame and QuitGame
}

void Application::CreateNewGame()
{
    _game = std::make_unique<Game>();
}

void Application::PlayGame()
{
    _game->Resume();

    long desiredFrameDurationInMs = 1000 / 60; // milliseconds per frame, at 60 frames per second

    while (true)
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
