#include "noughtsAndCrosses.hpp"
#include <iostream>
#include "../lib/p6/include/p6/p6.h"

void drawBoard(size_t numberColumsAndLines, p6::Context& ctx)
{
    for (size_t y = 0; y < numberColumsAndLines; y++) {
        for (size_t x = 0; x < numberColumsAndLines; x++) {
            const float red            = 1. / static_cast<float>(numberColumsAndLines) * static_cast<float>(x);
            const float blue           = 1. / static_cast<float>(numberColumsAndLines) * static_cast<float>(y);
            ctx.stroke                 = p6::Color{red, 0.f, blue, 1.f};
            float horizontalCoordinate = p6::map<float>(static_cast<float>(x), 0.f, static_cast<float>(numberColumsAndLines), -1.f, 1.f);
            float verticalCoordinate   = p6::map<float>(static_cast<float>(y), 0.f, static_cast<float>(numberColumsAndLines), 1.f, -1.f);
            ctx.square(p6::TopLeftCorner{horizontalCoordinate, verticalCoordinate}, 1. / static_cast<float>(numberColumsAndLines));
        }
    }
}

void playNoughtsAndCrosses()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int  height = 900;
        int  width  = 900;
        auto ctx    = p6::Context{{height, width, "Nought And Crosses"}};
        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            // Clear the objects that were drawn during the previous update
            ctx.background({0.5f, 0.3f, 0.5f});
            // Draw the board
            drawBoard(3, ctx);
        };
        // Start the program
        ctx.start();
    }
    // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}