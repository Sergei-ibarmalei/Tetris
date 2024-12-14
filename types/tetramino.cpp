#include <cmath>
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
        bool leftCrossed {false};
        bool rightCrossed {false};
        for (const auto& pixel: turnedSprite)
        {
            if (pixel.col < 0)
            {
                leftCrossed = true;
                break;
            } 
            if (pixel.col == WORKAREA_COL) 
            {
                rightCrossed = true;
                break;
            }
        }

        if (leftCrossed)
        {
            for (auto& pixel: turnedSprite)
            {
                pixel.col += 1;
            }
            return;
        }
        if (rightCrossed)
        {
            for (auto& pixel: turnedSprite)
            {
                pixel.col -= 1;
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
        }
        MakeRealTetramino();
        RecomputeRealTetraminoRects();

    }



    TetStore::TetStore()
    {
        vStore.reserve(ALLTETRAMINOS);
        vStore.assign({
            TetraminoPlane(createPlaneV()),
            TetraminoCube(createCubeV()),
            TetraminoL(createLV()),
            TetraminoG(createGV()),
            TetraminoRight(createRightV()),
            TetraminoLeft(createLeftV()),
            TetraminoT(createTV())
        });
    }


}


