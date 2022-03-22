#include "noughtsAndCrosses.hpp"
#include <iostream>
#include "../lib/p6/include/p6/p6.h"

struct CellIndex {
    int x;
    int y;
};

void drawASquareAtIndex(CellIndex cell, size_t boardSize, p6::Context& ctx)
{
    float horizontalCoordinate = p6::map<float>(static_cast<float>(cell.x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
    float verticalCoordinate   = p6::map<float>(static_cast<float>(cell.y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
    ctx.square(p6::TopLeftCorner{horizontalCoordinate, verticalCoordinate}, 1. / static_cast<float>(boardSize));
}

void drawBoard(size_t boardSize, p6::Context& ctx)
{
    for (size_t y = 0; y < boardSize; y++) {
        for (size_t x = 0; x < boardSize; x++) {
            const float red            = 1. / static_cast<float>(boardSize) * static_cast<float>(x);
            const float blue           = 1. / static_cast<float>(boardSize) * static_cast<float>(y);
            ctx.use_stroke             = false;
            ctx.fill                   = p6::Color{red, 0.8f, blue, 1.f};
            float horizontalCoordinate = p6::map<float>(static_cast<float>(x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
            float verticalCoordinate   = p6::map<float>(static_cast<float>(y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
            ctx.square(p6::TopLeftCorner{horizontalCoordinate, verticalCoordinate}, 1. / static_cast<float>(boardSize));
        }
    }
}

CellIndex findHoveredCell(glm::vec2 mouse, size_t boardSize)
{
    float horizontalCoordinate = p6::map<float>(static_cast<float>(mouse.x), -1.f, 1.f, 0.f, static_cast<float>(boardSize));
    float verticalCoordinate   = p6::map<float>(static_cast<float>(mouse.y), 1.f, -1.f, 0.f, static_cast<float>(boardSize));
    // std::cout << "x = " << horizontalCoordinate << " y = " << verticalCoordinate << std::endl;
    CellIndex hoveredCell = {static_cast<int>(horizontalCoordinate), static_cast<int>(verticalCoordinate)};
    return hoveredCell;
}

void playNoughtsAndCrosses()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int    height    = 900;
        int    width     = 900;
        auto   ctx       = p6::Context{{height, width, "Nought And Crosses"}};
        size_t boardSize = 3;
        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            // Clear the objects that were drawn during the previous update
            ctx.background({0.5f, 0.3f, 0.5f});
            drawBoard(boardSize, ctx);
            CellIndex hoveredCell = findHoveredCell(ctx.mouse(), boardSize);
            //std::cout << "x = " << hoveredCell.x << " y = " << hoveredCell.y << std::endl;
            ctx.fill = p6::Color{0.f, 0.f, 0.f, 1.f};
            drawASquareAtIndex(hoveredCell, boardSize, ctx);
        };

        // Start the program
        ctx.start();
    }
    // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}