#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include "pixel.hpp"

namespace tetris
{
    class TetrisRoom
    {
        private:
        std::array<Pixel, WORKAREA_ARRAYLENGTH> room;
        std::array<int, WORKAREA_ROW>           list_countOfFilledPixelInRow;
        size_t                                  filledRoomSize {0};

        // vector of row's nomber that must be deleted:
        std::vector<size_t>                     list_rowsToDelete;
        void                                    checkRowsToDelete();


        public:
        TetrisRoom();
        void ShowRoom(SDL_Renderer* r);
        const std::array<Pixel, WORKAREA_ARRAYLENGTH>& GetRoom() const {
            return room;
        }
        void FixTetramino(const std::array<Pixel, TETRAMINOLENGTH>& realTetramino);
        bool RoomIsEmpty() const {return filledRoomSize == 0;}
        bool List_RowsToDeleteIsEmpty() const {return list_rowsToDelete.empty();}
        void RemoveFilledRows();

        #ifdef LOGS
            friend std::ostream& operator<<(std::ostream& os, const TetrisRoom& tr);
        #endif


    };

}