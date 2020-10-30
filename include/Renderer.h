#ifndef CATCH_GAME_RENDERER_H
#define CATCH_GAME_RENDERER_H

#include "Game.h"

#include <SDL.h>

#include <cstdint>
#include <map>
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
    Renderer(std::string gameName);
    ~Renderer();

    bool InitialisedSuccessfully() const;
    void RenderGame(const Game& game, const uint32_t framesPerSecond);
    void WindowSizeChanged(int newWidth, int newHeight);

  private:
    bool InitialiseSDL();
    bool InitialiseWindow();
    bool InitialiseRenderer();
    bool InitialisePNGLoading();
    bool InitialiseSpriteMap();
    bool ImportSpriteToMap(std::string spriteName, std::string pathToSpriteFile);
    SDL_Surface* LoadSpriteSurface(std::string spriteFilePath);

    void RefreshWindowTitle(const uint32_t points, const uint32_t framesPerSecond,
                            const bool isPaused);

    void RenderCatcher(const Game& game);
    void RenderFallers(const Game& game);

    void SetRenderColour(const Colour c);
    void SetRenderColour(const Colour c, const Uint8 alpha);
    void RefreshRegionHeights();

    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

  private:
    bool _initialisedSuccessfully;
    std::string _gameName;
    int _windowWidth{0};
    int _windowHeight{0};
    int _catcherRegionHeight{0};
    int _fallersRegionHeight{0};
    std::map<std::string, SDL_Texture*> _spriteMap;
    SDL_Window* _sdl_Window{nullptr};
    SDL_Renderer* _sdl_Renderer{nullptr};
};

#endif
