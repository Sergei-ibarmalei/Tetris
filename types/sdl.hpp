#pragma once

#include <SDL2/SDL.h>
#include "../consts/const.hpp"
#include "defs.hpp"

#ifdef LOGS
    #include <iostream>
#endif

namespace tetris
{
    class SDL
    {
        private:
        SDL_Window*     window {nullptr};
        SDL_Renderer*   render {nullptr};
        SDL_Event e;
        bool inits {true};

        public:
        SDL(const char* appName);
        SDL(const SDL&) = delete;
        SDL& operator=(const SDL&) = delete;
        SDL(SDL&&) = delete;
        SDL&& operator=(SDL&&) = delete;
        ~SDL();

        SDL_Renderer* Render() {return render;}
        SDL_Event& Event() {return e;}
        bool InitOk() const {return inits;}
    };


}