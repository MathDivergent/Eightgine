#include <SDL.h>

namespace Eightgine
{

int fMain(int iArgumentCount, char** pArgumentValues)
{
    // TODO: example code
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return 1;
    }

    auto pWindow = SDL_CreateWindow("EightgineEditor", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (pWindow == nullptr)
    {
        SDL_Quit();
        return 1;
    }

    auto pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (pRenderer == nullptr)
    {
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        return 1;
    }

    auto const iFPS = 60;
    auto const iFrameDelay = 1000 / iFPS;

    auto bRunning = true;
    SDL_Event aEvent;


    while (bRunning)
    {
        auto iFrameStart = SDL_GetTicks();

        while (SDL_PollEvent(&aEvent))
        {
            if (aEvent.type == SDL_QUIT)
            {
                bRunning = false;
            }
        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0xff);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);

        auto iFrameTime = SDL_GetTicks() - iFrameStart;
        if (iFrameTime < iFrameDelay)
        {
            SDL_Delay(iFrameDelay - iFrameTime);
        }
    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    // ~
    return 0;
}

} // namespace Eightgine
