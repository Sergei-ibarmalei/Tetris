#include <vector>
#include "pixel.hpp"

constexpr std::vector<tetris::Pixel> createPlane()
{
    std::vector<tetris::Pixel> v;
    v.assign({tetris::Pixel(0, 7),       tetris::Pixel(0, 8),       tetris::Pixel(0, 9),       tetris::Pixel(0, 10),
              tetris::Pixel(1, 7, true), tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true), tetris::Pixel(1, 10, true),
              tetris::Pixel(2, 7),       tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
              tetris::Pixel(3, 7),       tetris::Pixel(3, 8),       tetris::Pixel(3, 9),       tetris::Pixel(3, 10)});
    return v;
}


constexpr std::vector<tetris::Pixel> createCube()
{
    std::vector<tetris::Pixel> v;
    v.assign({tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true),
              tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true),
              });
    return v;
}



constexpr std::vector<tetris::Pixel> createL()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8, true), tetris::Pixel(1, 9),       tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10)
    });
    return v;
}


constexpr std::vector<tetris::Pixel> createG()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9),       tetris::Pixel(1, 10, true),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10)
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createRight()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8),       tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8, true), tetris::Pixel(1, 9, true), tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createLeft()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9, true), tetris::Pixel(1, 10, true),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}

constexpr std::vector<tetris::Pixel> createT()
{
    std::vector<tetris::Pixel> v;
    v.assign({
            tetris::Pixel(0, 8, true), tetris::Pixel(0, 9, true), tetris::Pixel(0, 10, true),
            tetris::Pixel(1, 8),       tetris::Pixel(1, 9, true), tetris::Pixel(1, 10),
            tetris::Pixel(2, 8),       tetris::Pixel(2, 9),       tetris::Pixel(2, 10),
    });
    return v;
}

