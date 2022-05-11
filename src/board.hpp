#pragma once
#include "../lib/p6/include/p6/p6.h"

// size of a board (number of cells in row/column)
struct BoardSize {
    size_t w;
    size_t h;
};

// coordinates in the window
struct Coordinates {
    float x;
    float y;
};

// index of a cell in the board
struct CellIndex {
    int x;
    int y;
};

// draw a board with different width/height
void drawRectangleBoard(BoardSize boardSize, p6::Context& ctx);
// return the color value associated to a coordinate (to draw the board with a gradient)
float colorOfIndex(int x, size_t boardSize);
// return the color of a cell
p6::Color colorOfPosition(int x, int y, BoardSize boardSize);
// find the size of the side of the square cell
float sideOfCell(BoardSize boardSize, const p6::Context& ctx);
//take the coordinates in the board and return the coordinates in p6 window
Coordinates convertIntoWindowCoordinates(int x, int y, BoardSize boardSize, const p6::Context& ctx);
