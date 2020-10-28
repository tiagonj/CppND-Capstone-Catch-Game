#include "InputReader.h"

#include "SDL.h"

void InputReader::ReadInputs(ApplicationInputs& appInputs, GameInputs& gameInputs)
{
    // Reset inputs
    appInputs.pauseIsPressed = false;
    appInputs.quitIsPressed = false;
    gameInputs.moveLeftIsPressed = false;
    gameInputs.moveRightIsPressed = false;

    // Poll for any available SDL events
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
        {
            appInputs.quitIsPressed = true;
        }
        else if (ev.type == SDL_KEYDOWN)
        {
            switch (ev.key.keysym.sym)
            {
                case SDLK_LEFT:
                {
                    gameInputs.moveLeftIsPressed = true;
                    break;
                }
                case SDLK_RIGHT:
                {
                    gameInputs.moveRightIsPressed = true;
                    break;
                }
                case SDLK_p:
                {
                    appInputs.pauseIsPressed = true;
                }
                default:
                {
                    // Do nothing
                    break;
                }
            }
        }
    }
}
