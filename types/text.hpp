#pragma once
#include <vector>




namespace tetris
{

    constexpr std::vector<unsigned char> createSS() {
        std::vector<unsigned char> v;
        v.assign({
            0, 1, 1, 1, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 0,
            0, 1, 1, 1, 0,
            0, 0, 0, 1, 1,
            0, 0, 0, 1, 1,
            0, 0, 0, 1, 1,
            1, 1, 1, 1, 0
        });
        return v;
    }

    constexpr std::vector<unsigned char> createSC()
    {
        std::vector<unsigned char> v;
        v.assign({
            0, 1, 1, 1, 0,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            0, 1, 1, 1, 0,
        });
        return v;
    }

    constexpr std::vector<unsigned char> createSO()
    {
        std::vector<unsigned char> v;
        v.assign({
            0, 1, 1, 1, 0,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
            0, 1, 1, 1, 0
        });
        return v;
    }

    constexpr std::vector<unsigned char> createSR()
    {
        std::vector<unsigned char> v;
        v.assign({
            1, 1, 1, 0, 0,
            1, 1, 0, 1, 0,
            1, 1, 0, 1, 0,
            1, 1, 1, 1, 0,
            1, 1, 1, 0, 0,
            1, 1, 0, 1, 0,
            1, 1, 0, 0, 1,
            1, 1, 0, 0, 1,
        });
        return v;
    }

    constexpr std::vector<unsigned char> createSE()
    {
        std::vector<unsigned char> v;
        v.assign({
            1, 1, 1, 1, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 0,
            1, 1, 1, 1, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 0,
            1, 1, 1, 1, 1
        });
        return v;
    }
}