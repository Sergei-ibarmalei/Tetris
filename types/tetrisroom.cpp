#include "tetrisroom.hpp"

namespace tetris
{

    TetrisRoom::TetrisRoom()
    {
        for (size_t r = 0; r < WORKAREA_ROW; ++r)
        {
            for (size_t c = 0; c < WORKAREA_COL; ++c)
            {
                room[r * WORKAREA_COL + c].row = static_cast<int>(r);
                room[r * WORKAREA_COL + c].col = static_cast<int>(c);
                room[r * WORKAREA_COL + c].filled = false;
                room[r * WORKAREA_COL + c].RecomputeRectangle();
            }
        }
    }



    void TetrisRoom::FixTetramino(const std::array<Pixel, TETRAMINOLENGTH>& realTetramino)
    {
        for (const auto& pixel: realTetramino)
        {
            auto pixelRow = static_cast<size_t>(pixel.row);
            if (pixelRow < 0) pixelRow = 0UL;
            if (pixelRow > WORKAREA_ROW) pixelRow = WORKAREA_ROW;
            auto pixelCol = static_cast<size_t>(pixel.col);
            
            if (pixelCol < 0) pixelCol = 0UL;
            if (pixelCol > WORKAREA_COL) pixelCol = WORKAREA_COL;
            const auto atPixel  = pixelRow * WORKAREA_COL + pixelCol;
            room[atPixel].filled = pixel.filled;
            room[atPixel].pColor = pixel.pColor;

            list_countOfFilledPixelInRow[pixelRow] += 1;
        }
        filledRoomSize += TETRAMINOLENGTH;
        checkRowsToDelete();

    }

    void TetrisRoom::ShowRoom(SDL_Renderer* r)
    {
        for (const auto& pixel: room)
        {
            if (pixel.filled)
            {
                auto tmpColor = pixel.pColor;
                SDL_SetRenderDrawColor(r, tmpColor.red, tmpColor.green, tmpColor.blue, tmpColor.alpha);
                //SDL_RenderDrawRect(r, &pixel.pixelRect);
                SDL_RenderFillRect(r, &pixel.pixelRect);
            }
        }
    }

    void TetrisRoom::checkRowsToDelete()
    {
        for (size_t rowToDelete = 0; rowToDelete < WORKAREA_ROW; ++rowToDelete)
        {
            if (list_countOfFilledPixelInRow[rowToDelete] == WORKAREA_COL)
                list_rowsToDelete.push_back(rowToDelete);
        }
    }



    void TetrisRoom::RemoveFilledRows()
    {
        size_t indexToDelete;
        for (indexToDelete= 0; indexToDelete < list_rowsToDelete.size(); ++indexToDelete)
        {
            // get the nomber of row that has to be deleted:
            auto row_toDelete = list_rowsToDelete[indexToDelete];

            // delete this row:
            for (size_t column = 0; column < WORKAREA_COL; ++column)
            {
                room[row_toDelete * WORKAREA_COL + column].filled = false;
                list_countOfFilledPixelInRow[row_toDelete] = 0;
                filledRoomSize -= WORKAREA_COL;
            }
            
            // move down everything that above: 
            for (int r = (static_cast<int>(row_toDelete) - 1); r >= 0; --r)
            {
                for (size_t c = 0; c < WORKAREA_COL; ++c)
                {
                    auto AT = static_cast<size_t>(r) * WORKAREA_COL + c;
                    auto DOWN = static_cast<size_t>(r + 1) * WORKAREA_COL + c;
                    if (room[AT].filled)
                    {
                        auto tmpColor = room[AT].pColor;
                        room[DOWN].filled = true;
                        room[DOWN].pColor = tmpColor;
                        room[AT].filled = false;

                    }
                }
            }
        }
        list_rowsToDelete.clear();

        // here we count the amount of filled pixels in every row
        // and save it in list_countOfFilledPixelInRow:
        for (size_t atRow = 0; atRow < WORKAREA_ROW; ++atRow)
        {
            list_countOfFilledPixelInRow[atRow] = static_cast<int>(std::count_if(
                room.begin() + atRow * WORKAREA_COL,
                room.begin() + (atRow+1) * WORKAREA_COL,
                [](const Pixel& p) {return p.filled;}
            ));
        }
    }

    bool TetrisRoom::CanWeContinue()
    {
        const auto firstRow8ColBusy  {room.at(WORKAREA_COL + 8).filled};
        const auto firstRow9ColBusy  {room.at(WORKAREA_COL + 9).filled};
        const auto firstRow10ColBusy {room.at(WORKAREA_COL + 10).filled};
        return !(firstRow8ColBusy || firstRow9ColBusy || firstRow10ColBusy);
    }


    #ifdef LOGS
    std::ostream& operator<<(std::ostream& os, const TetrisRoom& tr)
    {
        /*const auto& firstRow8ColBusy  = tr.room.at(WORKAREA_ROW + 8).filled;
        const auto& firstRow9ColBusy  = tr.room.at(WORKAREA_ROW + 9).filled;
        const auto& firstRow10ColBusy = tr.room.at(WORKAREA_ROW + 10).filled;*/

        /*os << "list count of filled pixel in row: \n";
        int row = 0;
        for (const auto& c: tr.list_countOfFilledPixelInRow)
        {
            os << row++ << " :\t" << "[" << c << "]\n";
        }
        os << "Rows to delete: \n";
        if (tr.list_rowsToDelete.empty()) os << "list is empty!\n";
        else 
        {
            for (const auto r: tr.list_rowsToDelete)
            {
                os << "[" << r << "]\n";
            }
        }*/
        int in = 0;
        for (size_t r = 0; r < WORKAREA_ROW; ++r)
        {
            os << in++;
            for (size_t c = 0; c < WORKAREA_COL; ++c)
            {
                if (tr.room[r* WORKAREA_COL + c].filled) os << "[*] ";
                else os << "[ ] ";
            }
            os << std::endl;
        }

        /*if (firstRow8ColBusy)
        {
            os << "first row 8 busy\n";
        } 
        else os << "first row 8 is free\n";
        if (firstRow9ColBusy)
        {
            os << "first row 9 busy\n";
        } 
        else os << "first row 9 is free\n";
        if (firstRow10ColBusy) 
        {
            os << "first row 10 busy\n";
        }
        else os << "first row 10 is free\n";*/
        return os;
    }
    #endif
 
}