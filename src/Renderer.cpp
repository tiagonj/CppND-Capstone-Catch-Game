#include "Renderer.h"

#include <SDL.h>

#include <cstdint>
#include <iostream>

#define CATCHER_REGION_HEIGHT_IN_PERCENT ((float)0.1f)
#define CATCHER_HEIGHT_IN_PERCENT_OF_REGION ((float)0.33f)

static constexpr Colour _kBackgroundColour{.r = 0x1E, .g = 0x1E, .b = 0x1E};
static constexpr Colour _kCatcherColour{.r = 0xFF, .g = 0xFF, .b = 0xFF};
static constexpr Colour _kTempFallerColour{.r = 0xFF, .g = 0xFF, .b = 0xFF}; // TODO REMOVE

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
    // Clear screen
    SetRenderColour(_kBackgroundColour);
    SDL_RenderClear(_sdl_Renderer);

    // Region heights
    int catcherRegionHeight = CATCHER_REGION_HEIGHT_IN_PERCENT * _windowHeight;
    int fallersRegionHeight = _windowHeight - catcherRegionHeight;

    RenderCatcher(game, catcherRegionHeight);
    RenderFallers(game, fallersRegionHeight);

    // Update screen rendering
    SDL_RenderPresent(_sdl_Renderer);

    // Refresh window title text
    RefreshWindowTitle(game.Points(), game.NumberOfFallers(), framesPerSecond, game.IsPaused());
}

void Renderer::RenderCatcher(const Game& game, const int catcherRegionHeight)
{
    SDL_Rect catcher;

    float catcherLeftPos = game.CatcherLeftEdgePositionInPercent();
    float catcherRightPos = game.CatcherRightEdgePositionInPercent();

    catcher.h = CATCHER_HEIGHT_IN_PERCENT_OF_REGION * catcherRegionHeight;
    catcher.w = (catcherRightPos - catcherLeftPos) * _windowWidth;
    catcher.x = catcherLeftPos * _windowWidth;
    catcher.y = _windowHeight - catcherRegionHeight;

    SetRenderColour(_kCatcherColour);
    SDL_RenderFillRect(_sdl_Renderer, &catcher);
}

void Renderer::RenderFallers(const Game& game, const int fallersRegionHeight)
{
    SetRenderColour(_kTempFallerColour);

    std::vector<const Faller*> v = game.GetAllFallers();

    for (auto& f : v)
    {
        SDL_Rect faller;

        // Screen coordinates are such that Y = 0 means top of screen, whereas in
        // the Game world 0.0 means bottom. Thus we need to convert up & down here
        float up = 1.0 - f->UpPosition();
        float down = 1.0 - f->DownPosition();
        float left = f->LeftPosition();
        float right = f->RightPosition();

        float height = up - down;
        float width = right - left;

        faller.h = height * fallersRegionHeight;
        faller.w = width * _windowWidth;
        faller.x = left * _windowWidth;
        faller.y = up * fallersRegionHeight;

        faller.y = std::max(faller.y, 0);

        SDL_RenderFillRect(_sdl_Renderer, &faller);
    }
}

void Renderer::RefreshWindowTitle(const uint32_t points, const uint32_t nrOfFallers,
                                  const uint32_t framesPerSecond, const bool isPaused)
{
    std::string title{_gameName + " Points: " + std::to_string(points) + " (" +
                      std::to_string(framesPerSecond) +
                      " fps) Number of fallers: " + std::to_string(nrOfFallers)};

    if (isPaused)
    {
        title += " [Paused]";
    }

    SDL_SetWindowTitle(_sdl_Window, title.c_str());
}

void Renderer::WindowSizeChanged(int newWidth, int newHeight)
{
    _windowWidth = newWidth;
    _windowHeight = newHeight;
    SDL_RenderPresent(_sdl_Renderer);
}

void Renderer::SetRenderColour(const Colour c)
{
    SetRenderColour(c, SDL_ALPHA_OPAQUE);
}

void Renderer::SetRenderColour(const Colour c, const Uint8 alpha)
{
    SDL_SetRenderDrawColor(_sdl_Renderer, c.r, c.g, c.b, alpha);
}
