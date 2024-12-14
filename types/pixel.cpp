#include "pixel.hpp"

namespace tetris
{
    #ifdef LOGS
    std::ostream& operator<<(std::ostream& os, const Pixel& pixel)
    {
        os << "[" << pixel.pixelRect.x << ',' << pixel.pixelRect.y <<
            ',' << pixel.pixelRect.w << ',' << pixel.pixelRect.h << "] " <<
            "row_col: [" << pixel.row << ',' << pixel.col << "]";
        os << " [" << "most left: " << std::boolalpha << pixel.mostLeft << ", " <<
                      "most right: " << std::boolalpha << pixel.mostRight << "]";
                      /*"most high " << std::boolalpha << pixel.mostHigh << ", " <<
                      "most low  " << std::boolalpha << pixel.mostLow << "]\n";*/
        os << " rect: {" << pixel.pixelRect.x << ' ' << pixel.pixelRect.y << ' ' <<
            pixel.pixelRect.w << ' ' << pixel.pixelRect.h << "}";
        os << " col: [" << static_cast<int>(pixel.pColor.red) << ',' << 
            static_cast<int>(pixel.pColor.green) << ','<< static_cast<int>(pixel.pColor.blue) << "]\n";
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, const Color& c)
    {
        return os << " r:" << c.red << " g:" << c.green << " b:" << c.blue;
    }
    #endif

    void Pixel::RecomputeRectangle()
    {
        pixelRect.x = LEFTWALL_X + (static_cast<int>(col) * CELL_SIDE) + PIXEL_SIDE_SHIFT;
        pixelRect.y = LEFTWALL_Y + (static_cast<int>(row) * CELL_SIDE) + PIXEL_SIDE_SHIFT;
        pixelRect.w = pixelRect.h = CELL_SIDE - PIXEL_SIDE_SHIFT;
    }
}