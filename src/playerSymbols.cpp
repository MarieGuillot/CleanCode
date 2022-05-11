#include "playerSymbols.hpp"
#include <algorithm>
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"

p6::Color colorOfPositionInvertedWithAlpha(int x, int y, BoardSize boardSize, float alphaColor)
{
    if ((x + y) % 2 == 1) {
        return p6::Color{0.f, 0.f, 0.f, alphaColor};
    }
    else {
        const float red  = colorOfIndex(static_cast<int>(x), boardSize.w);
        const float blue = colorOfIndex(static_cast<int>(y), boardSize.h);
        return p6::Color{red, 1.f, blue, alphaColor};
    }
}

void drawCrossAtIndex(const CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor)
{
    Coordinates coordinates    = convertIntoWindowCoordinates(cell.x, cell.y, boardSize, ctx);
    const float halfSideOfCell = sideOfCell(boardSize, ctx);
    ctx.fill                   = colorOfPositionInvertedWithAlpha(cell.x, cell.y, boardSize, alphaColor);
    auto rotation              = p6::Angle(p6::Radians(M_PI / 4.));
    ctx.rectangle(p6::Center{coordinates.x + halfSideOfCell, coordinates.y - halfSideOfCell}, // Center on the current mouse position
                  p6::Radii(halfSideOfCell / 4.f, halfSideOfCell),
                  rotation);
    ctx.rectangle(p6::Center{coordinates.x + halfSideOfCell, coordinates.y - halfSideOfCell}, // Center on the current mouse position
                  p6::Radii(halfSideOfCell / 4.f, halfSideOfCell),
                  -rotation);
}

void drawWhiteCrossOverTheBoard(p6::Context& ctx)
{
    float ratio   = std::min(ctx.aspect_ratio(), 1.f);
    ctx.fill      = p6::Color{1.f, 1.f, 1.f, 1.f};
    auto rotation = p6::Angle(p6::Radians(M_PI / 4.));
    ctx.rectangle(p6::Center{0.f, 0.f},
                  p6::Radii(ratio * 0.2f, ratio * 0.8f),
                  rotation);
    ctx.rectangle(p6::Center{0.f, 0.f},
                  p6::Radii(ratio * 0.2f, ratio * 0.8f),
                  -rotation);
}

void drawNoughtAtIndex(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor)
{
    Coordinates coordinates    = convertIntoWindowCoordinates(cell.x, cell.y, boardSize, ctx);
    const float halfSideOfCell = sideOfCell(boardSize, ctx);
    ctx.fill                   = colorOfPositionInvertedWithAlpha(cell.x, cell.y, boardSize, alphaColor);
    ctx.circle(p6::Center{coordinates.x + halfSideOfCell, coordinates.y - halfSideOfCell}, // Center on the current mouse position
               p6::Radius{
                   static_cast<float>(0.8 * halfSideOfCell)});
    p6::Color color = colorOfPosition(cell.x, cell.y, boardSize);
    ctx.fill        = color;
    ctx.circle(p6::Center{coordinates.x + halfSideOfCell, coordinates.y - halfSideOfCell}, // Center on the current mouse position
               p6::Radius{
                   static_cast<float>(0.5 * halfSideOfCell)});
}

void drawWhiteNoughtOverTheBoard(p6::Context& ctx, p6::Color backgroundColor)
{
    float ratio = std::min(ctx.aspect_ratio(), 1.f);
    ctx.fill    = p6::Color{1.f, 1.f, 1.f, 1.f};
    ctx.circle(p6::Center{0.f, 0.f},
               p6::Radius{ratio * 0.8f});
    ctx.fill = backgroundColor;
    ctx.circle(p6::Center{0.f, 0.f},
               p6::Radius{ratio * 0.5f});
}

void drawPlayerSymbol(const CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor, Player player)
{
    switch (player) {
    case Player::Cross:
        drawCrossAtIndex(cell, boardSize, ctx, alphaColor);
        break;
    case Player::Nought:
        drawNoughtAtIndex(cell, boardSize, ctx, alphaColor);
        break;
    }
}

void drawWinner(BoardSize boardSize, std::optional<Player> winner, p6::Context& ctx)
{
    p6::Color backgroundColor = colorOfPosition(boardSize.w / 2, boardSize.h / 2, boardSize);

    ctx.background(backgroundColor);
    if (winner != std::nullopt) {
        switch (*winner) {
        case Player::Cross:
            drawWhiteCrossOverTheBoard(ctx);
            break;
        case Player::Nought:
            drawWhiteNoughtOverTheBoard(ctx, backgroundColor);
            break;
        }
    }
}