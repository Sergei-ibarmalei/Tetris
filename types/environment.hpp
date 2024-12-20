#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <array>
#include "../consts/const.hpp"
#include "sdl.hpp"


namespace tetris
{
    class Environment
    {
        private:
        SDL_Rect leftBorder;
        SDL_Rect rightBorder;
        SDL_Rect floor;

        std::unique_ptr<std::array<SDL_Point, WORKAREA_ARRAYLENGTH>> envPoints;

        public:
        Environment();
        Environment(const Environment&) = delete;
        Environment(Environment&&) = delete;
        Environment& operator=(const Environment&) = delete;
        void ShowEnv(SDL_Renderer* r);
        SDL_Point GetStart() const {return {LEFTWALL_X, LEFTWALL_Y};}

    };
}