#include "boardGame.hpp"
#include <algorithm>
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "playerSymbols.hpp"

CellIndex convertIntoBoardCoordinates(float x, float y, BoardSize boardSize, const p6::Context& ctx)
{
    float sideSquare      = sideOfCell(boardSize, ctx);
    float halfWidthBoard  = boardSize.w * sideSquare;
    float halfHeightBoard = boardSize.h * sideSquare;

    float     boardX           = (x + halfWidthBoard) / (2.f * sideSquare);
    float     boardY           = (halfHeightBoard - y) / (2.f * sideSquare);
    CellIndex boardCoordinates = {static_cast<int>(floor(boardX)), static_cast<int>(floor(boardY))};
    return boardCoordinates;
}

std::optional<CellIndex> findHoveredCell(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx)
{
    CellIndex boardCoordinates = convertIntoBoardCoordinates(mouse.x, mouse.y, boardSize, ctx);
    if (boardCoordinates.x >= 0 && boardCoordinates.x < static_cast<int>(boardSize.w) && boardCoordinates.y >= 0 && boardCoordinates.y < static_cast<int>(boardSize.h)) {
        return boardCoordinates;
    }
    else {
        return std::nullopt;
    }
}

std::optional<int> findHoveredColumn(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx)
{
    std::optional<CellIndex> hoveredCell = findHoveredCell(mouse, boardSize, ctx);

    if (hoveredCell) {
        return hoveredCell->x;
    }
    else {
        return std::nullopt;
    }
}

Player changePlayer(Player player)
{
    return static_cast<Player>((static_cast<int>(player) + 1) % 2);
}