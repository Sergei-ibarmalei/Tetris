#include "sdl.hpp"

namespace tetris
{
    SDL::SDL(const char* appName)
    {
        if (!appName)
        {
            #ifdef LOGS
            std::cout << "App name is absent, abort.\n";
            inits = false;
            return;
            #endif
        }
        if (SDL_Init(SDL_INIT_VIDEO) < 0 ||
            !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            #ifdef LOGS
            std::cout << "Cannot initialize SDL, abort.\n";
            inits = false;
            return;
            #endif
        }
        window = SDL_CreateWindow(appName,
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_W,
                                SCREEN_H,
                                SDL_WINDOW_SHOWN);
        if (!window)
        {
            #ifdef LOGS
            std::cout << "Cannot initialize window, abort.\n";
            inits = false;
            return;
            #endif
        }

        render = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

        if (!render)
        {
            #ifdef LOGS
            std::cout << "Cannot initialize render, abort.\n";
            inits = false;
            return;
            #endif
        }
    }




    SDL::~SDL()
    {
        if (render)
        {
            SDL_DestroyRenderer(render);
            render = nullptr;
        }
        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        SDL_Quit();
    }
}