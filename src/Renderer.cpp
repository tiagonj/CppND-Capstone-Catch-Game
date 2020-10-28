#include "Renderer.h"

#include <SDL.h>

#include <cstdint>
#include <iostream>

static constexpr Colour _kBackgroundColour{.r = 0x1E, .g = 0x1E, .b = 0x1E};
static constexpr Colour _kCatcherColour{.r = 0xFF, .g = 0xFF, .b = 0xFF};

Renderer::Renderer(std::string gameName, int windowWidth, int windowHeight)
    : _gameName(gameName),
      _windowWidth(windowWidth),
      _windowHeight(windowHeight)
{
    if (0 == SDL_Init(SDL_INIT_VIDEO))
    {
        _sdl_Window =
            SDL_CreateWindow(_gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                             windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if (nullptr == _sdl_Window)
        {
            std::cerr << "Failed to create Window using SDL library\n";
            std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";
        }
        else
        {
            _sdl_Renderer = SDL_CreateRenderer(_sdl_Window, -1, SDL_RENDERER_ACCELERATED);
            if (nullptr == _sdl_Renderer)
            {
                std::cerr << "Failed to create Renderer using SDL library\n";
                std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";

                SDL_DestroyWindow(_sdl_Window);
                _sdl_Window = nullptr;
            }
        }

        if ((nullptr == _sdl_Window) || (nullptr == _sdl_Renderer))
        {
            SDL_Quit();
        }
    }
    else
    {
        std::cerr << "Failed to initilise SDL library\n";
        std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer()
{
    if (nullptr != _sdl_Window)
    {
        SDL_DestroyWindow(_sdl_Window);
    }

    SDL_Quit();
}

void Renderer::RenderGame(const Game& game, const uint32_t framesPerSecond)
{
    RefreshWindowTitle(game.Points(), game.NumberOfFallers(), framesPerSecond, game.IsPaused());

    // Clear screen
    SetRenderColour(_kBackgroundColour);
    SDL_RenderClear(_sdl_Renderer);

    // float left = game.CatcherLeftEdgePositionInPercent();
    // float right = game.CatcherRightEdgePositionInPercent();

    // TODO
    // TODO
    // TODO
    // TODO

    SDL_RenderPresent(_sdl_Renderer);
}

void Renderer::RefreshWindowTitle(const uint32_t points, const uint32_t nrOfFallers,
                                  const uint32_t framesPerSecond, const bool isPaused)
{
    std::string title{_gameName + " Points: " + std::to_string(points) +
                      " (FPS: " + std::to_string(framesPerSecond) +
                      ") Number of fallers: " + std::to_string(nrOfFallers)};

    if (isPaused)
    {
        title += " [Paused]";
    }

    SDL_SetWindowTitle(_sdl_Window, title.c_str());
}

void Renderer::SetRenderColour(const Colour c)
{
    SetRenderColour(c, SDL_ALPHA_OPAQUE);
}

void Renderer::SetRenderColour(const Colour c, const Uint8 alpha)
{
    SDL_SetRenderDrawColor(_sdl_Renderer, c.r, c.g, c.b, alpha);
}
