#ifndef CATCH_GAME_RENDERER_H
#define CATCH_GAME_RENDERER_H

#include "Game.h"

#include <SDL.h>

#include <cstdint>
#include <string>

typedef struct _colour_t
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} Colour;

class Renderer
{
  public:
    Renderer(std::string gameName, int windowWidth, int windowHeight);
    ~Renderer();

    bool InitialisedSuccessfully() const;
    void RenderGame(const Game& game, const uint32_t framesPerSecond);
    void RefreshWindowTitle(const uint32_t points, const uint32_t framesPerSecond,
                            const bool isPaused);

    void WindowSizeChanged(int newWidth, int newHeight);

  private:
    bool InitialiseSDL();
    bool InitialiseWindow(int windowWidth, int windowHeight);
    bool InitialiseRenderer();
    bool InitialisePNGLoading();

    void RenderCatcher(const Game& game, const int catcherRegionHeight);
    void RenderFallers(const Game& game, const int fallersRegionHeight);

    void SetRenderColour(const Colour c);
    void SetRenderColour(const Colour c, const Uint8 alpha);

    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

  private:
    bool _initialisedSuccessfully;
    std::string _gameName;
    int _windowWidth{0};
    int _windowHeight{0};
    SDL_Window* _sdl_Window{nullptr};
    SDL_Renderer* _sdl_Renderer{nullptr};
};

#endif
