#pragma once

constexpr int SCREEN_W {2200};
constexpr int SCREEN_H {1300};
constexpr int SCREENCENTER_X {SCREEN_W / 2};
constexpr int SCREENCENTER_Y {SCREEN_H / 2};

constexpr int CELL_SIDE {50};
constexpr size_t WORKAREA_ROW {24};
constexpr size_t WORKAREA_COL {18};
constexpr size_t WORKAREA_ARRAYLENGTH {WORKAREA_ROW * WORKAREA_COL};
constexpr size_t FLOOR {WORKAREA_ROW - 1};
constexpr int PIXEL_SIDE_SHIFT {3};

constexpr int WORKAREA_WIDTH  {WORKAREA_COL * CELL_SIDE};
constexpr int WORKAREA_HEIGHT {WORKAREA_ROW * CELL_SIDE};

constexpr int LEFTWALL_X {SCREENCENTER_X - (WORKAREA_WIDTH / 2)};
constexpr int LEFTWALL_Y {CELL_SIDE};

constexpr int RIGHTWALL_X {SCREENCENTER_X + (WORKAREA_WIDTH / 2)};
constexpr int RIGHTWALL_Y {LEFTWALL_Y};

constexpr int LEFTFLOOR_X {LEFTWALL_X};
constexpr int RIGHTFLOOR_X {RIGHTWALL_X};

constexpr int LEFTFLOOR_Y {LEFTWALL_Y + (CELL_SIDE * WORKAREA_ROW)};
constexpr int RIGHTFLOOR_Y {LEFTFLOOR_Y};

constexpr int BORDER_WIDTH {50};
constexpr int LEFTBORDER_X {LEFTWALL_X - BORDER_WIDTH};
constexpr int LEFTBORDER_Y {LEFTWALL_Y};
constexpr int RIGHTBORDER_X {RIGHTWALL_X};
constexpr int RIGHTBORDER_Y {RIGHTWALL_Y};
constexpr int BORDER_HEIGHT {(LEFTFLOOR_Y - LEFTWALL_Y) + BORDER_WIDTH};

//constexpr int FLOOR_WIDTH {WORKAREA_WIDTH};
constexpr int FLOOR_WIDTH {RIGHTWALL_X - LEFTWALL_X};
constexpr int FLOOR_HEIGHT {BORDER_HEIGHT};



constexpr size_t TETRAMINOLENGTH{4u};

enum class TetraminoKind {Plane, Cube, L, G, Right, Left, T, all};
enum class TetraminoColor {Crimson, DeepPink, OrangeRed, LimeGreen, 
                            DarkCyan, Cornflowerblue, Chocolate, all};
enum class MoveSideDirection {Right, Left, Down};
constexpr size_t SPRITELENGTH {16};
constexpr size_t SPRITELENGTH4 {16};
constexpr size_t SPRITELENGTH3 {9};
constexpr size_t SPRITELENGTH2 {4};

/*enum class TurnsKinds {first, second, third, fourth, all};
constexpr size_t TETRAMINOALL {static_cast<size_t>(TetraminoKind::all)};
enum class FigureStates: size_t {FarLeft, MostLeft, MiddleLeft, Left, Initial, Right, MiddleRight, MostRight, FarRight, all};

constexpr size_t FIGURESTATE_LENGTH {static_cast<size_t>(FigureStates::all)};*/


//constexpr auto ALLTURNS {static_cast<size_t>(TurnsKinds::all)};

constexpr size_t TETRAMINO_PLANE   {0};
constexpr size_t TETRAMINO_CUBE    {1};
constexpr size_t TETRAMINO_L       {2};
constexpr size_t TETRAMINO_G       {3};
constexpr size_t TETRAMINO_RIGHT   {4};
constexpr size_t TETRAMINO_LEFT    {5};
constexpr size_t TETRAMINO_T       {6};
constexpr size_t ALLTETRAMINOS     {static_cast<size_t>(TetraminoKind::all)};


constexpr size_t GUITETRAMINOARRAY_LENGTH {16};
constexpr int    GUITETRAMINOROOM_SIDE  {4};
constexpr int    GUITETRAMINOROOM_WIDTH {300};
constexpr int    GUITETRAMINOCELL_SIDE {GUITETRAMINOROOM_WIDTH / 
    GUITETRAMINOROOM_SIDE};










