#include "types/core.hpp"

int main(int argc, char** argv)
{
    using namespace tetris;

    if (!entry()) return 1;

    tetgame();
    
    return 0;
}