#include "InputReader.h"
#include "Renderer.h"

#include "SDL.h"

void InputReader::ReadInputs(ApplicationInputs& appInputs, GameInputs& gameInputs,
                             Renderer& renderer)
{
    // Reset inputs
    appInputs.pauseIsPressed = false;
    appInputs.quitIsPressed = false;
    gameInputs.moveLeftIsPressed = false;
    gameInputs.moveRightIsPressed = false;

    // Obtain left/right key state directly from keyboard
    // state so as to continuously process these
    // (From: https://gamedev.stackexchange.com/a/19583)
    const Uint8* state = SDL_GetKeyboardState(NULL);
    gameInputs.moveLeftIsPressed = (1 == state[SDL_SCANCODE_LEFT]);
    gameInputs.moveRightIsPressed = (1 == state[SDL_SCANCODE_RIGHT]);

    // Cycle through all available SDL events
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_QUIT)
        {
            appInputs.quitIsPressed = true;
        }
        else if (ev.type == SDL_WINDOWEVENT)
        {
            if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                renderer.WindowSizeChanged(ev.window.data1, ev.window.data2);
            }
        }
        else if (ev.type == SDL_KEYDOWN)
        {
            switch (ev.key.keysym.sym)
            {
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
