#include "board.hpp"
#include <algorithm>
#include <iostream>
#include "../lib/p6/include/p6/p6.h"

float colorOfIndex(int x, size_t boardSize)
{
    return 1.f / static_cast<float>(boardSize) * static_cast<float>(x);
}

p6::Color colorOfPosition(int x, int y, BoardSize boardSize)
{
    if ((x + y) % 2 == 0) {
        return p6::Color{0.f, 0.f, 0.f, 1.f};
    }
    else {
        const float red  = colorOfIndex(static_cast<int>(x), boardSize.w);
        const float blue = colorOfIndex(static_cast<int>(y), boardSize.h);
        return p6::Color{red, 1.f, blue, 1.f};
    }
}

// to adjust the board when the user resize the window, find it is the width or the height that limits the board's drawing
// return the size (in p6 space) of the "limiting factor" (i.e. width or height of the board)
float referenceLengthToDrawTheBoard(BoardSize boardSize, const p6::Context& ctx)
{
    float ratio      = ctx.aspect_ratio();
    float boardRatio = static_cast<float>(boardSize.w) / static_cast<float>(boardSize.h);
    if (ratio < boardRatio) { // The board is limited by the width of the window.
        return ratio;
    }
    else { // The board is limited by the height of the window.
        return 1.f;
    }
}

float sideOfCell(BoardSize boardSize, const p6::Context& ctx)
{
    float ratio           = ctx.aspect_ratio();
    float boardRatio      = static_cast<float>(boardSize.w) / static_cast<float>(boardSize.h);
    float referenceLength = referenceLengthToDrawTheBoard(boardSize, ctx);
    float sideOfCell      = 1.f;
    if (ratio < boardRatio) { // The board is limited by the width of the window.
        sideOfCell = referenceLength / static_cast<float>(boardSize.w);
    }
    else { // The board is limited by the height of the window.
        sideOfCell = referenceLength / static_cast<float>(boardSize.h);
    }
    return sideOfCell;
}

Coordinates convertIntoWindowCoordinates(int x, int y, BoardSize boardSize, const p6::Context& ctx)
{
    float sideSquare      = sideOfCell(boardSize, ctx);
    float halfWidthBoard  = boardSize.w * sideSquare;
    float halfHeightBoard = boardSize.h * sideSquare;

    Coordinates WindowCoordinates = {-halfWidthBoard + x * 2 * sideSquare, halfHeightBoard - y * 2 * sideSquare};
    return WindowCoordinates;
}

void drawRectangleBoard(BoardSize boardSize, p6::Context& ctx)
{
    for (size_t y = 0; y < boardSize.h; y++) {
        for (size_t x = 0; x < boardSize.w; x++) {
            p6::Color color         = colorOfPosition(x, y, boardSize);
            ctx.fill                = color;
            ctx.use_stroke          = false;
            p6::Color stroke        = {1., 1., 1., 1.};
            ctx.stroke              = stroke;
            Coordinates coordinates = convertIntoWindowCoordinates(x, y, boardSize, ctx);
            float       sideSquare  = sideOfCell(boardSize, ctx);
            ctx.square(p6::TopLeftCorner{coordinates.x, coordinates.y}, sideSquare);
        }
    }
}
