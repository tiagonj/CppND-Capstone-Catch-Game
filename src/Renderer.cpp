#include "Renderer.h"

#include <SDL.h>
#include <SDL_image.h>

#include <cstdint>
#include <experimental/filesystem>
#include <iostream>

using dir_it = std::experimental::filesystem::directory_iterator;

#define CATCHER_REGION_HEIGHT_IN_PERCENT ((float)0.1f)
#define CATCHER_HEIGHT_IN_PERCENT_OF_REGION ((float)0.25f)

#define DEFAULT_WINDOW_WIDTH (800)
#define DEFAULT_WINDOW_HEIGHT (DEFAULT_WINDOW_WIDTH * (1.0f + CATCHER_REGION_HEIGHT_IN_PERCENT))

static constexpr Colour _kBackgroundColour{.r = 0x1E, .g = 0x1E, .b = 0x1E};
static constexpr Colour _kCatcherColour{.r = 0xFF, .g = 0xFF, .b = 0xFF};
static constexpr Colour _kFallbackFallerColour{.r = 0xE6, .g = 0x5C, .b = 0x00};

Renderer::Renderer(std::string gameName)
    : _initialisedSuccessfully(false),
      _gameName(gameName),
      _windowWidth(DEFAULT_WINDOW_WIDTH),
      _windowHeight(DEFAULT_WINDOW_HEIGHT),
      _catcherRegionHeight(0),
      _fallersRegionHeight(0)
{
    RefreshRegionHeights();

    bool success = true;
    success &= success && InitialiseSDL();
    success &= success && InitialiseWindow();
    success &= success && InitialiseRenderer();
    success &= success && InitialisePNGLoading();
    success &= success && InitialiseSpriteMap();
    _initialisedSuccessfully = success;
}

Renderer::~Renderer()
{
    if (nullptr != _sdl_Window)
    {
        SDL_DestroyWindow(_sdl_Window);
    }

    for (auto& s : _spriteMap)
    {
        SDL_DestroyTexture(s.second);
    }

    SDL_Quit();
}

bool Renderer::InitialisedSuccessfully() const
{
    return _initialisedSuccessfully;
}

void Renderer::RenderGame(const Game& game, const uint32_t framesPerSecond)
{
    // Clear screen
    SetRenderColour(_kBackgroundColour);
    SDL_RenderClear(_sdl_Renderer);

    // Render Catcher and Faller objects
    RenderCatcher(game);
    RenderFallers(game);

    // Update screen rendering
    SDL_RenderPresent(_sdl_Renderer);

    // Refresh window title text
    RefreshWindowTitle(game.Points(), framesPerSecond, game.IsPaused());
}

void Renderer::WindowSizeChanged(int newWidth, int newHeight)
{
    _windowWidth = newWidth;
    _windowHeight = newHeight;
    RefreshRegionHeights();
    SDL_RenderPresent(_sdl_Renderer);
}

bool Renderer::InitialiseSDL()
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initilise SDL library\n";
        std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

bool Renderer::InitialiseWindow()
{
    _sdl_Window =
        SDL_CreateWindow(_gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         _windowWidth, _windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (nullptr == _sdl_Window)
    {
        std::cerr << "Failed to create Window using SDL library\n";
        std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

bool Renderer::InitialiseRenderer()
{
    _sdl_Renderer = SDL_CreateRenderer(_sdl_Window, -1, SDL_RENDERER_SOFTWARE);

    if (nullptr == _sdl_Renderer)
    {
        std::cerr << "Failed to create Renderer using SDL library\n";
        std::cerr << "SDL_Error(): " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

bool Renderer::InitialisePNGLoading()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cerr << "Failed to initialise PNG image loading using SDL library\n";
        std::cerr << "IMG_GetError(): " << IMG_GetError() << "\n";
        return false;
    }
    return true;
}

bool Renderer::InitialiseSpriteMap()
{
    bool success = true;
    std::string spriteDir = "../sprites/";

    for (auto it = dir_it(spriteDir); (it != dir_it()) && success; ++it)
    {
        if ((std::experimental::filesystem::is_regular_file(it->path())) &&
            (it->path().extension() == ".png"))
        {
            success &= ImportSpriteToMap(it->path().stem(), it->path());
        }
    }

    return success;
}

bool Renderer::ImportSpriteToMap(std::string spriteName, std::string pathToSpriteFile)
{
    // Sprite must not have been loaded before
    if (_spriteMap.find(spriteName) != _spriteMap.end())
    {
        std::cerr << "ERROR: sprite " << spriteName << " (" << pathToSpriteFile
                  << ") already loaded\n";
        return false;
    }

    // See
    SDL_Surface* spriteSurface = LoadSpriteSurface(pathToSpriteFile);

    if (NULL == spriteSurface)
    {
        return false;
    }

    // See: https://stackoverflow.com/a/28729213
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_sdl_Renderer, spriteSurface);
    SDL_FreeSurface(spriteSurface);

    if (NULL == texture)
    {
        std::cerr << "ERROR: failed to convert " << spriteName << " sprite to an SDL texture\n";
        return false;
    }

    _spriteMap[spriteName] = texture;
    return true;
}

SDL_Surface* Renderer::LoadSpriteSurface(std::string spriteFilePath)
{
    // This method is heavily based on the code found in this tutorial
    // https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
    SDL_Surface* convertedSurface = NULL;

    // Load image surface (NOTE: must be Free'd)
    SDL_Surface* imageSurface = IMG_Load(spriteFilePath.c_str());
    if (NULL == imageSurface)
    {
        std::cerr << "Failed to load sprite at " << spriteFilePath << "\n";
        std::cerr << "IMG_GetError(): " << IMG_GetError() << "\n";
    }
    else
    {
        // Get the SDL surface associated with the window (NOTE: must *not* be Free'd)
        SDL_Surface* windowSurface = SDL_GetWindowSurface(_sdl_Window);
        convertedSurface = SDL_ConvertSurface(imageSurface, windowSurface->format, 0);
        if (NULL == convertedSurface)
        {
            std::cerr << "Failed to convert sprite surface\n";
            std::cerr << "SDL_GetError(): " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(imageSurface);
    }

    return convertedSurface;
}

void Renderer::RefreshWindowTitle(const uint32_t points, const uint32_t framesPerSecond,
                                  const bool isPaused)
{
    std::string title{_gameName + " Points: " + std::to_string(points) + " (" +
                      std::to_string(framesPerSecond) + " fps)"};

    if (isPaused)
    {
        title += " [Paused]";
    }

    SDL_SetWindowTitle(_sdl_Window, title.c_str());
}

void Renderer::RenderCatcher(const Game& game)
{
    SDL_Rect catcher;

    float catcherLeftPos = game.CatcherLeftEdgePositionInPercent();
    float catcherRightPos = game.CatcherRightEdgePositionInPercent();

    catcher.h = CATCHER_HEIGHT_IN_PERCENT_OF_REGION * _catcherRegionHeight;
    catcher.w = (catcherRightPos - catcherLeftPos) * _windowWidth;
    catcher.x = catcherLeftPos * _windowWidth;
    catcher.y = _windowHeight - _catcherRegionHeight;

    SetRenderColour(_kCatcherColour);
    SDL_RenderFillRect(_sdl_Renderer, &catcher);
}

void Renderer::RenderFallers(const Game& game)
{
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

        std::string& spriteName = f->Name();

        float height = down - up;
        float width = right - left;

        faller.h = height * _fallersRegionHeight;
        faller.w = width * _windowWidth;
        faller.x = left * _windowWidth;
        faller.y = up * _fallersRegionHeight;

        faller.y = std::max(faller.y, 0);

        auto sprite_it = _spriteMap.find(spriteName);
        if (sprite_it == _spriteMap.end())
        {
            // Fallback in case sprite not loaded
            SetRenderColour(_kFallbackFallerColour);
            SDL_RenderFillRect(_sdl_Renderer, &faller);
        }
        else
        {
            SDL_RenderCopyEx(_sdl_Renderer, sprite_it->second,
                             /* whole texture */ NULL,
                             /* destination rect */ &faller,
                             /* angle */ 0.0,
                             /* center of rotation */ NULL,
                             /* flip texture */ SDL_FLIP_NONE);
        }
    }
}

void Renderer::SetRenderColour(const Colour c)
{
    SetRenderColour(c, SDL_ALPHA_OPAQUE);
}

void Renderer::SetRenderColour(const Colour c, const Uint8 alpha)
{
    SDL_SetRenderDrawColor(_sdl_Renderer, c.r, c.g, c.b, alpha);
}

void Renderer::RefreshRegionHeights()
{
    _catcherRegionHeight = CATCHER_REGION_HEIGHT_IN_PERCENT * _windowHeight;
    _fallersRegionHeight = _windowHeight - _catcherRegionHeight;
}
