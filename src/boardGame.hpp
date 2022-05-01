#pragma once
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"

enum class Player {
    Cross,
    Nought
};

CellIndex                convertIntoBoardCoordinates(float x, float y, BoardSize boardSize, const p6::Context& ctx);
std::optional<CellIndex> findHoveredCell(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx);
std::optional<int>       findHoveredColumn(glm::vec2 mouse, BoardSize boardSize, const p6::Context& ctx);
Player                   changePlayer(Player player);