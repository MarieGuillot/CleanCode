#include "connect4.hpp"
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"

void playConnect4()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int       height    = 1200;
        int       width     = 800;
        auto      ctx       = p6::Context{{height, width, "Connect 4"}};
        BoardSize boardSize = {6, 4};

        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            // Clear the objects that were drawn during the previous update
            ctx.background({0.f, 0.f, 0.f});
            drawRectangleBoard(boardSize, ctx);
        };

        // Start the program
        ctx.start();
    }
    // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}