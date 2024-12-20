#include "environment.hpp"

#define RED 0xffu, 0u, 0u, 0xffu
#define GREY 0xfbu, 0xf6u, 0xf6u, 0xffu

namespace tetris
{
    Environment::Environment()
    {
        leftBorder = {LEFTBORDER_X, LEFTBORDER_Y,
            BORDER_WIDTH, BORDER_HEIGHT};
        rightBorder = {RIGHTBORDER_X, RIGHTBORDER_Y,
            BORDER_WIDTH, BORDER_HEIGHT};
        floor = {LEFTFLOOR_X, LEFTFLOOR_Y,
            FLOOR_WIDTH, FLOOR_HEIGHT};

        envPoints = std::make_unique<std::array<SDL_Point, WORKAREA_ARRAYLENGTH>>();

        constexpr auto startx = LEFTWALL_X + CELL_SIDE;
        constexpr auto starty = LEFTWALL_Y;
        constexpr auto ENV_ROW {WORKAREA_ROW};
        constexpr auto ENV_COL {WORKAREA_COL - 1};

        for (size_t r = 0; r < ENV_ROW; ++r)
        {
            for (size_t c = 0; c < ENV_COL; ++c)
            {
                envPoints->operator[](r * ENV_COL + c).x =
                    static_cast<int>(startx +  (c * CELL_SIDE));
                envPoints->operator[](r * ENV_COL + c).y =
                    static_cast<int>(starty + (r * CELL_SIDE));
            }
        }
    }

    void Environment::ShowEnv(SDL_Renderer* r)
    {

        // Draw environment points
        SDL_SetRenderDrawColor(r, GREY);
        for (const auto p: *envPoints) SDL_RenderDrawPoint(r, p.x, p.y);   

        // Draw walls and floor
        SDL_SetRenderDrawColor(r, RED);
        SDL_RenderFillRect(r, &leftBorder);
        SDL_RenderFillRect(r, &rightBorder);
        SDL_RenderFillRect(r, &floor);


    }

}


#undef RED
#undef GREY