#pragma once

//#include <tuple>
#include <memory>
#include <array>
#include <vector>
#include "../consts/const.hpp"
#include "pixel.hpp"
#include "defs.hpp"
//#include "core.hpp"

#ifdef LOGS
    #include <iostream>
#endif



constexpr std::vector<tetris::Pixel> createPlaneV()
{
    std::vector<tetris::Pixel> v;
    v.assign({tetris::Pixel(0, 7),       tetris::Pixel(0, 8),       tetris::Pixel(0, 9),       tetris::Pixel(0, 10),
              tetris::Pixel(1, 7, true), tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true), tetris::Pixel(1, 10, true),
              tetris::Pixel(2, 7),       tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
              tetris::Pixel(3, 7),       tetris::Pixel(3, 8),       tetris::Pixel(3, 9),       tetris::Pixel(3, 10)});
    return v;
}


constexpr std::vector<tetris::Pixel> createCubeV()
{
    std::vector<tetris::Pixel> v;
    v.assign({tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true),
              tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true),
              });
    return v;
}



constexpr std::vector<tetris::Pixel> createLV()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8, true), tetris::Pixel(1, 9),       tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10)
    });
    return v;
}


constexpr std::vector<tetris::Pixel> createGV()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9),       tetris::Pixel(1, 10, true),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10)
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createRightV()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8),       tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true), tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createLeftV()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9, true), tetris::Pixel(1, 10, true),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createTV()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9, true), tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}



namespace tetris
{

    constexpr Color crimson(0xDCu, 0x14u, 0x3Cu, 0xFFu);
    constexpr Color deeppink(0xFFu, 0x14u, 0x93u, 0xFFu);
    constexpr Color orangered(0xFFu, 0x45u, 0u, 0xFFu);
    constexpr Color limegreen(0x32u, 0xCDu, 0x32u, 0xFFu);
    constexpr Color darkcyan(0u, 0x8Bu, 0x8Bu, 0xFFu);
    constexpr Color cornflowerblue(0x64u, 0x95u, 0xEDu, 0xFFu);
    constexpr Color magenta(0xFFu, 0u, 0xFFu, 0xFF);

    class Tetramino
    {
        protected:
        std::vector<Pixel> sprite;
        std::array<Pixel, TETRAMINOLENGTH> tetramino;
        std::vector<Pixel> turnedSprite;
        //std::vector<Pixel> tmp_turnedSprite;
        TetraminoKind kind;
        bool movable {true};
        void checkCrossingBorders(std::vector<Pixel>& turnedSprite);

        
        Tetramino(const std::vector<Pixel>& vectorOfPixels, size_t sizeOfVector, 
                    const Color& c, TetraminoKind kind);
        void MakeRealTetramino();
        void RecomputeRealTetraminoRects();
        bool down_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room);
        bool right_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room);
        bool left_checkTetraminoHitFixed(const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room);

        public:
        void Show(SDL_Renderer* r);
        void TurnRight();
        void TurnLeft();
        void Moving(MoveSideDirection dir, const std::array<Pixel, WORKAREA_ARRAYLENGTH>& room);
        TetraminoKind Kind() const {return kind;}
        bool IsMovable() const {return movable;}
        const std::array<Pixel, TETRAMINOLENGTH>& RealTetramino() const {
            return tetramino;
        }

        #ifdef LOGS
            friend std::ostream& operator<<(std::ostream& os, const Tetramino& t);
        #endif
    };

    class TetraminoPlane final: public Tetramino
    {
        public:
        explicit TetraminoPlane(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH4, crimson, TetraminoKind::Plane) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoCube final: public Tetramino
    {
        public:
        explicit TetraminoCube(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH2, deeppink, TetraminoKind::Cube) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoL final: public Tetramino
    {
        public:
        explicit TetraminoL(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH3, orangered, TetraminoKind::L) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoG final: public Tetramino
    {
        public:
        explicit TetraminoG(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH3, limegreen, TetraminoKind::G) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoRight final: public Tetramino
    {
        public:
        explicit TetraminoRight(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH3, darkcyan, TetraminoKind::Right) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoLeft final: public Tetramino
    {
        public:
        explicit TetraminoLeft(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH3, cornflowerblue, TetraminoKind::Left) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };

    class TetraminoT final: public Tetramino
    {
        public:
        explicit TetraminoT(const std::vector<Pixel>& data):
            Tetramino(data, SPRITELENGTH3, magenta, TetraminoKind::T) {
                for (const auto& pixel: sprite) turnedSprite.emplace_back(pixel);
            }
    };


    class TetStore
    {
        private:
        std::vector<Tetramino> vStore;

        public:
        TetStore();
        std::unique_ptr<Tetramino> MakeTetramino(TetraminoKind tkind)
        {
            return std::make_unique<Tetramino>(vStore[static_cast<size_t>(tkind)]);
        }
        std::unique_ptr<Tetramino> MakeRandomTetramino(size_t random)
        {
            return std::make_unique<Tetramino>(vStore[random]);
        }
    };

}



