#pragma once
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"
#include "boardGame.hpp"

// draw symbols in a cell
void drawNoughtAtIndex(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor);
void drawCrossAtIndex(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor);

// draw symbols in full screen (to announce the winner)
void drawWhiteNoughtOverTheBoard(p6::Context& ctx, p6::Color backgroundColor);
void drawWhiteCrossOverTheBoard(p6::Context& ctx);

// draw the symbol of the param player in a cell
void drawPlayerSymbol(CellIndex cell, BoardSize boardSize, p6::Context& ctx, float alphaColor, Player player);
// draw the symbol of the param winner in a full screen
void drawWinner(BoardSize boardSize, std::optional<Player> winner, p6::Context& ctx);