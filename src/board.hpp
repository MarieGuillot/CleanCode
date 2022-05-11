#pragma once
#include "../lib/p6/include/p6/p6.h"

struct BoardSize {
    size_t w;
    size_t h;
};

struct Coordinates {
    float x;
    float y;
};

struct CellIndex {
    int x;
    int y;
};

void        drawRectangleBoard(BoardSize boardSize, p6::Context& ctx);
float       colorOfIndex(int x, size_t boardSize);
p6::Color   colorOfPosition(int x, int y, BoardSize boardSize);
float       sideOfCell(BoardSize boardSize, const p6::Context& ctx);
Coordinates convertIntoWindowCoordinates(int x, int y, BoardSize boardSize, const p6::Context& ctx);
