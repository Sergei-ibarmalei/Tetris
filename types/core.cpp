#include "core.hpp"



namespace tetris
{
    void makeTetramino(size_t random);
    void fix();
    void checkKeys(bool& quit);
    void renderLoop();

    static std::unique_ptr<SDL> sdl;
    static std::unique_ptr<Environment> environment;
    static std::unique_ptr<TetStore> tetraminoStore;
    static std::pair<TetraminoKind, std::unique_ptr<Tetramino>> currentTetramino;
    static std::unique_ptr<TetrisRoom> tetrisRoom;
    static std::unique_ptr<TRandom> tRandom;
    static bool quit;

    bool entry()
    {
        sdl = std::make_unique<SDL>("Tetris");
        if (sdl->InitOk() == false) return false;

        environment = std::make_unique<Environment>();
        tetraminoStore = std::make_unique<TetStore>();
        tetrisRoom = std::make_unique<TetrisRoom>();
        tRandom = std::make_unique<TRandom>();
        quit = false;


        return true;
    }

    void tetgame()
    {
        makeTetramino(tRandom->GetRandom());
        while(!quit)
        {
            checkKeys(quit);
            if (!currentTetramino.second->IsMovable()) fix();
            if (!tetrisRoom->List_RowsToDeleteIsEmpty())
            {
                tetrisRoom->RemoveFilledRows();
            }
            renderLoop();
        }
    }





    void makeTetramino(size_t random)
    {
        currentTetramino.second.release();
        currentTetramino.second = tetraminoStore->MakeRandomTetramino(random);
        currentTetramino.first  = currentTetramino.second->Kind();
    }


    void renderLoop()
    {
            SDL_SetRenderDrawColor(sdl->Render(), 0u, 0u, 0u, 0xffu);
            SDL_RenderClear(sdl->Render());
            environment->ShowEnv(sdl);
            currentTetramino.second->Show(sdl->Render());
            if (!tetrisRoom->RoomIsEmpty()) tetrisRoom->ShowRoom(sdl->Render());
            SDL_RenderPresent(sdl->Render());       
    }



    void fix()
    {
        tetrisRoom->FixTetramino(currentTetramino.second->RealTetramino());
        currentTetramino.second.release();
        makeTetramino(tRandom->GetRandom());
    }

    void checkKeys(bool& quit)
    {
        while(SDL_PollEvent(&sdl->Event()) != 0)
            {
                if (sdl->Event().type == SDL_QUIT) quit = true;
                else if (sdl->Event().type == SDL_KEYDOWN)
                {
                    switch(sdl->Event().key.keysym.sym)
                    {
                        #ifdef LOGS
                        case SDLK_p:
                        {
                            std::cout << *tetrisRoom << std::endl;
                            break;
                        }
                        #endif
                        case SDLK_d:
                        {
                            if (currentTetramino.first == TetraminoKind::Cube) break;
                            currentTetramino.second->TurnRight();
                            break;
                        }
                        case SDLK_a:
                        {
                            if (currentTetramino.first == TetraminoKind::Cube) break;
                            currentTetramino.second->TurnLeft();
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            currentTetramino.second->Moving(MoveSideDirection::Down,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            currentTetramino.second->Moving(MoveSideDirection::Left,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        case SDLK_RIGHT:
                        {
                            currentTetramino.second->Moving(MoveSideDirection::Right,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        default: {}
                    }
                }
            }
    }





}