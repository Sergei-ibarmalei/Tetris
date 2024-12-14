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
                room[r * WORKAREA_COL + c].RecomputeRectangle();
            }
        }
    }

    void TetrisRoom::fill_list_countOfFilledPixelInRow()
    {
        for (size_t atRow = 0; atRow < WORKAREA_ROW; ++atRow)
        {
            for (size_t atColumn = 0; atColumn < WORKAREA_COL; ++atColumn)
            {
                if (room[atRow * WORKAREA_COL + atColumn].filled) 
                    list_countOfFilledPixelInRow[atRow] += 1;
            }
        }
    }

    void TetrisRoom::clear_list_countOfFilledPixelInRow()
    {
        for (size_t i = 0; i < WORKAREA_ROW; ++i)
        {
            list_countOfFilledPixelInRow[i] = 0;
        }
    }

    void TetrisRoom::FixTetramino(const std::array<Pixel, TETRAMINOLENGTH>& realTetramino)
    {
        for (const auto& pixel: realTetramino)
        {
            const auto pixelRow = static_cast<size_t>(pixel.row);
            const auto pixelCol = static_cast<size_t>(pixel.col);
            const auto atPixel  = pixelRow * WORKAREA_COL + pixelCol;
            room[atPixel].filled = pixel.filled;
            room[atPixel].pColor = pixel.pColor;
        }
        filledRoomSize += TETRAMINOLENGTH;
        clear_list_countOfFilledPixelInRow();
        fill_list_countOfFilledPixelInRow();
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
        for (size_t count = 0; count < WORKAREA_ROW; ++count)
        {
            if (list_countOfFilledPixelInRow[count] == WORKAREA_COL)
                list_rowsToDelete.push_back(count);
        }
    }



    void TetrisRoom::RemoveFilledRows()
    {
        size_t time_toDelete;
        for (time_toDelete = 0; time_toDelete < list_rowsToDelete.size(); ++time_toDelete)
        {
            // get the nomber of row that has to be deleted:
            auto row_toDelete = list_rowsToDelete[time_toDelete];

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
        clear_list_countOfFilledPixelInRow();

        fill_list_countOfFilledPixelInRow();
    }


    #ifdef LOGS
    std::ostream& operator<<(std::ostream& os, const TetrisRoom& tr)
    {
        os << "list count of filled pixel in row: \n";
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
        }

        return os;
    }
    #endif
 
}