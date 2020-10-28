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

    void RenderGame(const Game& game, const uint32_t framesPerSecond);
    void RefreshWindowTitle(const uint32_t points, const uint32_t nrOfFallers,
                            const uint32_t framesPerSecond, const bool isPaused);

  private:
    void SetRenderColour(const Colour c);
    void SetRenderColour(const Colour c, const Uint8 alpha);

    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

  private:
    std::string _gameName;
    int _windowWidth{0};
    int _windowHeight{0};
    SDL_Window* _sdl_Window{nullptr};
    SDL_Renderer* _sdl_Renderer{nullptr};
};

#endif
