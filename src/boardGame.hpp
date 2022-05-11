#pragma once
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"

// Player (named after the symbol they use)
enum class Player {
    Cross,
    Nought
};

//take the coordinates in p6 windowand return the coordinates in the board
CellIndex convertIntoBoardCoordinates(float x, float y, BoardSize boardSize, const p6::Context& ctx);
//return the cell that is hovered by the player mouse
std::optional<CellIndex> findHoveredCell(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx);
//return the column of hovered cell
std::optional<int> findHoveredColumn(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx);
//if "cross" is given, return "nought", and vice versa
Player changePlayer(Player player);