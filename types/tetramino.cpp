#include <cmath>
#include <algorithm>
#include "tetramino.hpp"
#ifdef LOGS
    #include <string>
#endif


namespace tetris
{

    #ifdef LOGS
        std::ostream& operator<<(std::ostream& os, const Tetramino& t)
        {
            std::cout << "TETRAMINO SPRITE:\n";
            for (const auto& pixel: t.sprite) os << pixel << ' ';
            std::cout << "\n REAL TETRAMINO\n";
            for (const auto& pixel: t.tetramino) os << pixel << ' ';
            return os << std::endl;
        }
    #endif


    Tetramino::Tetramino(const std::vector<Pixel>& vectorOfPixels, 
                    size_t sizeOfVector, const Color& c, TetraminoKind kind)
    {
        this->kind = kind;
        sprite.reserve(sizeOfVector);
        turnedSprite.reserve(sizeOfVector);

        for (const auto& pixel: vectorOfPixels)
        {
            sprite.emplace_back(pixel);
            if (pixel.filled) sprite.back().SetColor(c); 
        } 
        MakeRealTetramino();
        RecomputeRealTetraminoRects();
    }

    void Tetramino::MakeRealTetramino()
    {
        size_t index {0};
        for (size_t i = 0; i < sprite.size(); ++i)
            if (sprite[i].filled) tetramino[index++] = sprite[i];
    }

    void Tetramino::RecomputeRealTetraminoRects()
    {
        for (auto& pixel: tetramino) pixel.RecomputeRectangle();
    }

    void Tetramino::Show(SDL_Renderer* r)
    {
        const auto color = tetramino[0].pColor;
        SDL_SetRenderDrawColor(r, color.red, color.green, color.blue, color.alpha);
        for (const auto& p: tetramino)
            //SDL_RenderDrawRect(r, &p.pixelRect); 
            SDL_RenderFillRect(r, &p.pixelRect);
    }

    void Tetramino::checkCrossingBorders(std::vector<Pixel>& turnedSprite)
    {
        for (const auto& pixel: turnedSprite)
        {
            if (pixel.col < 0)
            {
                for (auto& pixel: turnedSprite) pixel.col += 1;
                break;
            } 
            if (pixel.col == WORKAREA_COL) 
            {
                for (auto& pixel: turnedSprite) pixel.col -= 1;
                break;
            }
        }


    }



    void Tetramino::TurnRight()
    {
        if (!movable) return;
        size_t side {static_cast<size_t>(sqrt(sprite.size()))};

        for (size_t row = 0; row < side; ++row)
        {
            for (size_t col = 0; col < side; ++col)
            {
                turnedSprite[col * side + ((side - 1) - row)] = sprite[row * side + col];
            }
        }

        for (size_t row = 0; row < side; ++row)
        {
            for (size_t col = 0; col < side; ++col)
            {
                turnedSprite[row * side + col].row = sprite[row * side + col].row;
                turnedSprite[row * side + col].col = sprite[row * side + col].col;
            }
        }

        checkCrossingBorders(turnedSprite);
        // here we must check crossing boreder twice cuz of Plane nature 4x4
        if (this->kind == TetraminoKind::Plane) checkCrossingBorders(turnedSprite);

        sprite = turnedSprite; 
        MakeRealTetramino();
        RecomputeRealTetraminoRects();
    }

    void Tetramino::TurnLeft()
    {
        if (!movable) return;

        size_t side {static_cast<size_t>(sqrt(sprite.size()))};
        for (size_t row = 0; row < side; ++row)
        {
            for (size_t col = 0; col < side; ++col)
            {
                turnedSprite[((side - 1) - col) * side + row] = sprite[row * side + col];
            }
        }
        for (size_t row = 0; row < side; ++row)
        {
            for (size_t col = 0; col < side; ++col)
            {
                turnedSprite[row * side + col].row = sprite[row * side + col].row;
                turnedSprite[row * side + col].col = sprite[row * side + col].col;
            }
        }
        checkCrossingBorders(turnedSprite);
        // here we must check crossing boreder twice cuz of Plane nature 4x4
        if (this->kind == TetraminoKind::Plane) checkCrossingBorders(turnedSprite);

        sprite = turnedSprite;
        MakeRealTetramino();
        RecomputeRealTetraminoRects();
    }

    // check if we hit exist tetramino in room by moving down:
    bool Tetramino::down_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room)
    {
        for (const auto& pixel: tetramino)
        {
            auto fixedRow = pixel.row + 1;
            auto fixedCol = pixel.col;
            if (room[fixedRow * WORKAREA_COL + fixedCol].filled) return true;
        }
        return false;
    }

    // check if we hit exist tetramino in room by moving right:
    bool Tetramino::right_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room)
    {
        for (const auto& pixel: tetramino)
        {
            auto fixedRow = pixel.row;
            auto fixedCol = pixel.col + 1;
            if (room[fixedRow * WORKAREA_COL + fixedCol].filled) return true;
        }
        return false;
    }

    // check if we hit exist tetramino in room by moving left:
    bool Tetramino::left_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room)
    {
        for (const auto& pixel: tetramino)
        {
            auto fixedRow = pixel.row;
            auto fixedCol = pixel.col - 1;
            if (room[fixedRow * WORKAREA_COL + fixedCol].filled) return true;
        }
        return false;
    }

    void Tetramino::DropDown(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room)
    {
        while (movable)
        {
           for (const auto& pixel: tetramino)
            {
                if (down_checkTetraminoHitFixed(room))
                {
                    movable = false; break;
                }
                if ((pixel.row + 1) > static_cast<int>(FLOOR))
                {
                    movable = false; break;
                }
            }
            if (movable)
            {
                for (auto& pixel: sprite) pixel.row += 1;

            }
            MakeRealTetramino();
            RecomputeRealTetraminoRects();
        }
    }

    void Tetramino::Moving(MoveSideDirection dir, const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room)
    {
        if (!movable) return;

        switch (dir)
        {
            case MoveSideDirection::Down:
            {
                for (const auto& pixel: tetramino)
                {
                    if (down_checkTetraminoHitFixed(room))
                    {
                        movable = false; return;
                    }
                    if ((pixel.row + 1) > static_cast<int>(FLOOR))
                    {
                        movable = false; return;
                    }
                }
                for (auto& pixel: sprite) pixel.row += 1;
                break;
            }
            case MoveSideDirection::Right:
            {
                for (const auto& pixel: tetramino)
                {
                    if ( ((pixel.col + 1) > (static_cast<int>(WORKAREA_COL - 1))) ||
                        right_checkTetraminoHitFixed(room)) return;
                }
                for (auto& pixel: sprite) pixel.col += 1;
                break;
            }
            case MoveSideDirection::Left:
            {
                for (const auto& pixel: tetramino)
                {
                    if ( ((pixel.col - 1) < 0) ||
                        left_checkTetraminoHitFixed(room)) return;
                }
                for (auto& pixel: sprite) pixel.col -= 1;
                break;
            }
            default: {}
        }
        MakeRealTetramino();
        RecomputeRealTetraminoRects();

    }



    TetStore::TetStore()
    {
        vStore.reserve(ALLTETRAMINOS);
        vStore.assign({
            TetraminoPlane(createPlane()),
            TetraminoCube(createCube()),
            TetraminoL(createL()),
            TetraminoG(createG()),
            TetraminoRight(createRight()),
            TetraminoLeft(createLeft()),
            TetraminoT(createT())
        });
    }




    GUITetramino::GUITetramino()
    {
        initScoreTable();

        constexpr int guiTetraminoRoom_startX {
            (LEFTWALL_X  - GUITETRAMINOROOM_WIDTH) / 2
        };
        constexpr int guiTetraminoRoom_startY {
            SCREENCENTER_Y
        };
        for (size_t r = 0; r < GUITETRAMINOROOM_SIDE; ++r)
        {
            for (size_t c = 0; c < GUITETRAMINOROOM_SIDE; ++c)
            {
                const auto AT {r * static_cast<size_t>(GUITETRAMINOROOM_SIDE) + c};
                guiTetraminoRoom[AT].pixelRect.x = 
                    guiTetraminoRoom_startX + (static_cast<int>(c) * GUITETRAMINOCELL_SIDE);
                guiTetraminoRoom[AT].pixelRect.y = 
                    guiTetraminoRoom_startY + (static_cast<int>(r) * GUITETRAMINOCELL_SIDE);
                guiTetraminoRoom[AT].pixelRect.w = 
                    guiTetraminoRoom[AT].pixelRect.h = GUITETRAMINOCELL_SIDE;

            }
        }


    }



    void GUITetramino::makeTetramino(const std::vector<Pixel>& tetramino, size_t shift)
    {
        std::for_each(guiTetraminoRoom.begin(), guiTetraminoRoom.end(),
            [](Pixel& pixel){pixel.filled = false;});


        for (size_t pixel = 0; pixel < tetramino.size(); ++pixel)
        {
            if (tetramino[pixel].filled)
                guiTetraminoRoom[static_cast<size_t>(tetramino[pixel].row * 
                    GUITETRAMINOROOM_SIDE + (tetramino[pixel].col - shift))].filled = true;
        }


    }

    void GUITetramino::initScoreTable()
    {
        for (const auto& i: createSS())
        {
            i ? scoreTable[SYMBOL_S].emplace_back(SimplePixel(true)) :
                scoreTable[SYMBOL_S].emplace_back(SimplePixel());
        }
        setCoords({S_X, S_Y}, SYMBOL_S);

        for (const auto& i: createSC())
        {
            i ? scoreTable[SYMBOL_C].emplace_back(SimplePixel(true)) :
                scoreTable[SYMBOL_C].emplace_back(SimplePixel());
        }
        setCoords({C_X, C_Y}, SYMBOL_C);

        for (const auto& i: createSO())
        {
            i ? scoreTable[SYMBOL_O].emplace_back(SimplePixel(true)) :
                scoreTable[SYMBOL_O].emplace_back(SimplePixel());
        }
        setCoords({O_X, O_Y}, SYMBOL_O);

        for (const auto& i: createSR())
        {
            i ? scoreTable[SYMBOL_R].emplace_back(SimplePixel(true)) :
                scoreTable[SYMBOL_R].emplace_back(SimplePixel());
        }
        setCoords({R_X, R_Y}, SYMBOL_R);
        for (const auto& i: createSE())
        {
            i ? scoreTable[SYMBOL_E].emplace_back(SimplePixel(true)) :
                scoreTable[SYMBOL_E].emplace_back(SimplePixel());
        }
        setCoords({E_X, E_Y}, SYMBOL_E);
    }

    void GUITetramino::setCoords(const SDL_Point &startPoint, const size_t symbolNomber)
    {
        for (size_t r = 0; r < SCORESYMBOL_CELL_IN_HEIGHT; ++r)
        {
            for (size_t c = 0; c < SCORESYMBOL_CELL_IN_WIDTH; ++c)
            {
                const auto AT {r * SCORESYMBOL_CELL_IN_WIDTH + c};
                scoreTable[symbolNomber][AT].pRect.x =
                    startPoint.x + static_cast<int>(c) * SCORESYMBOL_CELLSIDE;
                scoreTable[symbolNomber][AT].pRect.y = 
                    startPoint.y + static_cast<int>(r) * SCORESYMBOL_CELLSIDE;
                scoreTable[symbolNomber][AT].pRect.w =
                    scoreTable[symbolNomber][AT].pRect.h = SCORESYMBOL_CELLSIDE;
            }
        }
    }

    void GUITetramino::MakeTetraminoForShow(TetraminoKind kind)
    {
        switch (kind)
        {
            case TetraminoKind::Plane:
            {
                makeTetramino(createPlane(), TETRAMINOSHIFTGUI_PLANE); return;
            }
            case TetraminoKind::Cube:
            {
                makeTetramino(createCube()); return;
            }
            case TetraminoKind::L:
            {
                makeTetramino(createL()); return;
            }
            case TetraminoKind::G:
            {
                makeTetramino(createG()); return;
            }
            case TetraminoKind::Right:
            {
                makeTetramino(createRight()); return;
            }
            case TetraminoKind::Left:
            {
                makeTetramino(createLeft()); return;
            }
            case TetraminoKind::T:
            {
                makeTetramino(createT()); return;
            }
            default: {}
        }
    }


    void GUITetramino::ShowNextTetramino(SDL_Renderer *r)
    {
        //constexpr Color cellColor(0xa9u, 0xa9u, 0xa9u);
        SDL_SetRenderDrawColor(r, beige.red, beige.green, beige.blue,
            beige.alpha);
        for (const auto& pixel: guiTetraminoRoom)
        {
            if(pixel.filled)  SDL_RenderDrawRect(r, &pixel.pixelRect);
        }
    }

    void GUITetramino::ShowScoreTable(SDL_Renderer *r)
    {
        SDL_SetRenderDrawColor(r, beige.red, beige.green, beige.blue, beige.alpha);
        for (const auto& v: scoreTable)
        {
            for (const auto& p: v)
                if (p.filled) SDL_RenderFillRect(r, &p.pRect);
        }
    }
}
