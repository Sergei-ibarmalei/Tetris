#include <thread>
#include "core.hpp"
#include "timer.hpp"





namespace tetris
{
    void initComplect();
    void reinitComplect();
    void fix();
    void checkKeys(bool& quit);
    void renderLoop();

    static std::unique_ptr<SDL> sdl;
    static std::unique_ptr<Environment> environment;
    static std::unique_ptr<TetStore> tetraminoStore;
    static std::unique_ptr<TetrisRoom> tetrisRoom;
    static std::unique_ptr<TRandom> tRandom;
    static std::unique_ptr<Timer>   tetrisTimer;
    static std::unique_ptr<Timer>   freezeBeforeDeleteTimer;
    static std::unique_ptr<GUITetramino> guiTetramino;
    static std::pair<std::pair<std::unique_ptr<Tetramino>, TetraminoKind>, TetraminoKind> tetraminoComplect;
    static bool quitGame;
    static int  freezeDuration; // duration in milliseconds
    static int  freezeBeforeDeleteDuration;

    bool entry()
    {
        sdl = std::make_unique<SDL>("Tetris");
        if (sdl->InitOk() == false) return false;

        environment = std::make_unique<Environment>();
        tetraminoStore = std::make_unique<TetStore>();
        tetrisRoom = std::make_unique<TetrisRoom>();
        tRandom = std::make_unique<TRandom>();
        tetrisTimer = std::make_unique<Timer>();
        freezeBeforeDeleteTimer = std::make_unique<Timer>();
        guiTetramino = std::make_unique<GUITetramino>();
        freezeDuration = 1000;
        freezeBeforeDeleteDuration = 200;
        quitGame = false;


        return true;
    }

    void tetgame()
    {
        initComplect();

        while(tetrisRoom->CanWeContinue() && !quitGame)
        {

            checkKeys(quitGame);
            if (tetrisTimer->hasElapsed())
            {
                tetraminoComplect.first.first->Moving(MoveSideDirection::Down,
                    tetrisRoom->GetRoom());
                tetrisTimer->reset();
                tetrisTimer->start(freezeDuration);
            }

            if (!tetraminoComplect.first.first->IsMovable()) fix ();

            if (!tetrisRoom->List_RowsToDeleteIsEmpty())
            {
                // freeze before delete row:
                freezeBeforeDeleteTimer->start(freezeBeforeDeleteDuration);
                while (!freezeBeforeDeleteTimer->hasElapsed())
                {
                    renderLoop();
                }
                freezeBeforeDeleteTimer->reset();
                // stop freeze befor delete row
                
                tetrisRoom->RemoveFilledRows();
            }
            renderLoop();

            // rest for CPU:
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }


    void initComplect()
    {
        auto randomIndex = static_cast<size_t>(tRandom->GetRandom());
        auto nextRandomIndex = static_cast<size_t>(tRandom->GetRandom());
        tetraminoComplect.first.first = tetraminoStore->MakeRandomTetramino(randomIndex);
        tetraminoComplect.first.second = static_cast<TetraminoKind>(randomIndex);
        tetraminoComplect.second = static_cast<TetraminoKind>(nextRandomIndex);
        guiTetramino->MakeTetraminoForShow(tetraminoComplect.second);
        tetrisTimer->start(freezeDuration);
    }

    // reinitiate complect after real tetramino is fixed:
    void reinitComplect()
    {
        auto nextRandomIndex = static_cast<size_t>(tRandom->GetRandom());
        tetraminoComplect.first.first.release();
        tetrisTimer->reset();
        tetraminoComplect.first.first = tetraminoStore->MakeRandomTetramino(
            static_cast<size_t>(tetraminoComplect.second)
        );
        tetraminoComplect.first.second = tetraminoComplect.second;
        tetraminoComplect.second = static_cast<TetraminoKind>(nextRandomIndex);
        guiTetramino->MakeTetraminoForShow(tetraminoComplect.second);
        tetrisTimer->start(freezeDuration);
    }


    void renderLoop()
    {
            SDL_SetRenderDrawColor(sdl->Render(), 0u, 0u, 0u, 0xffu);
            SDL_RenderClear(sdl->Render());
            environment->ShowEnv(sdl);
            tetraminoComplect.first.first->Show(sdl->Render());
            if (!tetrisRoom->RoomIsEmpty()) tetrisRoom->ShowRoom(sdl->Render());
            guiTetramino->ShowNextTetramino(sdl->Render());
            SDL_RenderPresent(sdl->Render());       
    }



    void fix()
    {
        tetrisRoom->FixTetramino(tetraminoComplect.first.first->RealTetramino());
        reinitComplect();
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
                            if (tetraminoComplect.first.second == TetraminoKind::Cube) break;
                            tetraminoComplect.first.first->TurnRight();
                            break;
                        }
                        case SDLK_a:
                        {
                            if (tetraminoComplect.first.second == TetraminoKind::Cube) break;
                            tetraminoComplect.first.first->TurnLeft();
                            break;
                        }
                        
                        case SDLK_SPACE: // press SPACE for drop down 
                        {
                            tetraminoComplect.first.first->DropDown(tetrisRoom->GetRoom());
                            fix();
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            tetraminoComplect.first.first->Moving(MoveSideDirection::Left,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        case SDLK_RIGHT:
                        {
                            tetraminoComplect.first.first->Moving(MoveSideDirection::Right,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        case SDLK_DOWN:
                        {
                            tetraminoComplect.first.first->Moving(MoveSideDirection::Down,
                                tetrisRoom->GetRoom());
                            break;
                        }
                        default: {}
                    }
                }
            }
    }

}