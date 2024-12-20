#pragma once

#include <SDL2/SDL.h>
#include "../consts/const.hpp"
#include "defs.hpp"

#ifdef LOGS
    #include <iostream>
#endif

namespace tetris
{

    struct Color
    {
        Uint8 red   {0u};
        Uint8 green {0u};
        Uint8 blue  {0u};
        Uint8 alpha {0xffu};
        constexpr Color(Uint8 r = 0u, Uint8 g = 0u, Uint8 b = 0u, Uint8 a = 0xffu) {
            red = r; green = g; blue = b; alpha = a;
        }
        constexpr Color(const Color& c) {
            red   = c.red;
            green = c.green;
            blue  = c.blue;
            alpha = c.alpha;
        }
        #ifdef LOGS
            friend std::ostream& operator<<(std::ostream& os, const Color& c);
        #endif
    };



    struct Pixel
    {
        int row {0};
        int col {0};
        Color pColor;
        SDL_Rect pixelRect {0, 0, 0, 0};
        bool mostLeft  {false};
        bool mostRight {false};
        bool filled    {false};
        constexpr Pixel(int r = 0, int c = 0, bool f = false)
        {
            row = r; col = c; filled = f;
        }
        void SetColor(const Color& c) {
            pColor = c;
        }
        void RecomputeRectangle();
        /*bool operator==(const Pixel& other) const
        {
            return this->row == other.row &&
                this->col == other.col;
        }

        // more left
        bool operator<(const Pixel& other) const 
        {
            return this->col < other.col;
        }

        // more right
        bool operator>(const Pixel& other) const 
        {
            return this->col > other.col;
        }*/


        #ifdef LOGS
            friend std::ostream& operator<<(std::ostream& os, const Pixel& pixel);
        #endif
    };

    struct SimplePixel
    {
        SDL_Rect pRect {};
        bool     filled {false};
        SimplePixel(bool f = false) {filled =f;}
    };



}