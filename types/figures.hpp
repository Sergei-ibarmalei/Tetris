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
/*#define pix tetris::Pixel

constexpr std::vector<tetris::Pixel> createSymbolS()
{
    std::vector<tetris::Pixel> a;
    a.assign({
        pix(0, 0),       pix(0, 1, true), pix(0, 2, true), pix(0, 3, true), pix(0, 4, true),
        pix(1, 0, true), pix(1, 1, true), pix(1, 2),       pix(1, 3),       pix(1, 4),
        pix(2, 0, true), pix(2, 1, true), pix(2, 2),       pix(2, 3),       pix(2, 4),
        pix(3, 0, true), pix(3, 1, true), pix(3, 2, true), pix(3, 3, true), pix(3, 4),
        pix(4, 0),       pix(4, 1),       pix(4, 2),       pix(4, 3, true), pix(4, 4, true),
        pix(5, 0),       pix(5, 1),       pix(5, 2),       pix(5, 3, true), pix(5, 4, true),
        pix(6, 0),       pix(6, 1),       pix(6, 2),       pix(6, 3, true), pix(6, 4, true),
        pix(7, 0, true), pix(7, 1, true), pix(7, 2, true), pix(7, 3, true), pix(7, 4)
    });
    return a;
}
#undef pix*/


