#pragma once
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"

enum class Player {
    Cross,
    Nought
};

void drawNoughtAtIndex(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor);
void drawCrossAtIndex(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor);
void drawWhiteNoughtOverTheBoard(p6::Context& ctx, p6::Color backgroundColor);
void drawWhiteCrossOverTheBoard(p6::Context& ctx);
void drawPlayerSymbol(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor, Player player);
void drawWinner(BoardSize boardSize, std::optional<Player> winner, p6::Context& ctx);