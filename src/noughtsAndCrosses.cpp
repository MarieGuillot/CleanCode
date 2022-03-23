#include "noughtsAndCrosses.hpp"
#include <math.h>
#include <iostream>
#include "../lib/p6/include/p6/p6.h"

struct CellIndex {
    int x;
    int y;
};

enum class Player {
    Cross,
    Nought
};

Player changePlayer(Player player)
{
    return static_cast<Player>((static_cast<int>(player) + 1) % 2);
}

void drawASquareAtIndex(CellIndex cell, size_t boardSize, p6::Context& ctx)
{
    float horizontalCoordinate = p6::map<float>(static_cast<float>(cell.x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
    float verticalCoordinate   = p6::map<float>(static_cast<float>(cell.y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
    ctx.square(p6::TopLeftCorner{horizontalCoordinate, verticalCoordinate}, 1. / static_cast<float>(boardSize));
}

float colorOfIndex(int x, size_t boardSize)
{
    return 1. / static_cast<float>(boardSize) * static_cast<float>(x);
}

void drawNoughtAtIndex(CellIndex cell, size_t boardSize, p6::Context& ctx, float alphaColor)
{
    const float horizontalCoordinate = p6::map<float>(static_cast<float>(cell.x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
    const float verticalCoordinate   = p6::map<float>(static_cast<float>(cell.y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
    const float halfSideOfCell       = 1. / boardSize;
    ctx.fill                         = p6::Color{1.f, 1.f, 1.f, alphaColor};
    ctx.circle(p6::Center{horizontalCoordinate + halfSideOfCell, verticalCoordinate - halfSideOfCell}, // Center on the current mouse position
               p6::Radius{
                   static_cast<float>(0.8 * halfSideOfCell)});
    const float red  = colorOfIndex(static_cast<int>(cell.x), boardSize);
    const float blue = colorOfIndex(static_cast<int>(cell.y), boardSize);
    ctx.fill         = p6::Color{red, 1.f, blue, 1.f};
    ctx.circle(p6::Center{horizontalCoordinate + halfSideOfCell, verticalCoordinate - halfSideOfCell}, // Center on the current mouse position
               p6::Radius{
                   static_cast<float>(0.5 * halfSideOfCell)});
}

void drawCrossAtIndex(const CellIndex cell, size_t boardSize, p6::Context& ctx, float alphaColor)
{
    const float horizontalCoordinate = p6::map<float>(static_cast<float>(cell.x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
    const float verticalCoordinate   = p6::map<float>(static_cast<float>(cell.y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
    const float halfSideOfCell       = 1. / boardSize;
    ctx.fill                         = p6::Color{1.f, 1.f, 1.f, alphaColor};
    auto rotation                    = p6::Angle(p6::Radians(M_PI / 4.));
    ctx.rectangle(p6::Center{horizontalCoordinate + halfSideOfCell, verticalCoordinate - halfSideOfCell}, // Center on the current mouse position
                  p6::Radii(halfSideOfCell / 4., halfSideOfCell),
                  rotation);
    ctx.rectangle(p6::Center{horizontalCoordinate + halfSideOfCell, verticalCoordinate - halfSideOfCell}, // Center on the current mouse position
                  p6::Radii(halfSideOfCell / 4., halfSideOfCell),
                  -rotation);
}

void drawPlayerSymbol(const CellIndex cell, size_t boardSize, p6::Context& ctx, float alphaColor, Player player)
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

void drawBoard(size_t boardSize, p6::Context& ctx)
{
    for (size_t y = 0; y < boardSize; y++) {
        for (size_t x = 0; x < boardSize; x++) {
            const float red                  = colorOfIndex(static_cast<int>(x), boardSize);
            const float blue                 = colorOfIndex(static_cast<int>(y), boardSize);
            ctx.use_stroke                   = false;
            ctx.fill                         = p6::Color{red, 1.f, blue, 1.f};
            const float horizontalCoordinate = p6::map<float>(static_cast<float>(x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
            const float verticalCoordinate   = p6::map<float>(static_cast<float>(y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
            ctx.square(p6::TopLeftCorner{horizontalCoordinate, verticalCoordinate}, 1. / static_cast<float>(boardSize));
        }
    }
}

std::optional<CellIndex> findHoveredCell(glm::vec2 mouse, size_t boardSize)
{
    if (mouse.x >= -1 && mouse.x <= 1 && mouse.y >= -1 && mouse.y <= 1) {
        float horizontalCoordinate = p6::map<float>(static_cast<float>(mouse.x), -1.f, 1.f, 0.f, static_cast<float>(boardSize));
        float verticalCoordinate   = p6::map<float>(static_cast<float>(mouse.y), 1.f, -1.f, 0.f, static_cast<float>(boardSize));
        // std::cout << "x = " << horizontalCoordinate << " y = " << verticalCoordinate << std::endl;
        CellIndex hoveredCell = {static_cast<int>(horizontalCoordinate), static_cast<int>(verticalCoordinate)};
        return hoveredCell;
    }
    else {
        return std::nullopt;
    }
}

std::vector<std::vector<bool>> createEmptyBoard(size_t boardSize)
{
    std::vector<std::vector<bool>> cellIsEmpty;
    for (size_t i = 0; i < boardSize; i++) {
        std::vector<bool> myLine;
        for (size_t j = 0; j < boardSize; j++) {
            myLine.push_back(true);
        }
        cellIsEmpty.push_back(myLine);
    }
    cellIsEmpty.shrink_to_fit();
    return cellIsEmpty;
}

void showBoard(const std::vector<std::vector<bool>>& board, const size_t boardSize)
{
    for (size_t i = 0; i < boardSize; i++) {
        std::cout << "Ma ligne : ";
        for (size_t j = 0; j < boardSize; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void playNoughtsAndCrosses()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int                            height      = 900;
        int                            width       = 900;
        auto                           ctx         = p6::Context{{height, width, "Nought And Crosses"}};
        size_t                         boardSize   = 3;
        Player                         player      = Player::Cross; //player 1 takes Crosses, player 2 takes Noughts
        std::vector<std::vector<bool>> cellIsEmpty = createEmptyBoard(boardSize);
        showBoard(cellIsEmpty, boardSize);
        std::vector<CellIndex>   playerCrossCells;
        std::vector<CellIndex>   playerNoughtsCells;
        std::optional<CellIndex> hoveredCell = std::nullopt;
        bool                     game        = true;

        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            // Clear the objects that were drawn during the previous update
            ctx.background({0.5f, 0.3f, 0.5f});

            drawBoard(boardSize, ctx);
            hoveredCell = findHoveredCell(ctx.mouse(), boardSize);
            ctx.fill    = p6::Color{0.f, 0.f, 0.f, 1.f};
            if (hoveredCell) {
                drawPlayerSymbol(*hoveredCell, boardSize, ctx, 0.5f, player);
            }

            for (CellIndex cell : playerCrossCells) {
                drawPlayerSymbol(cell, boardSize, ctx, 1.f, Player::Cross);
            }
            for (CellIndex cell : playerNoughtsCells) {
                drawPlayerSymbol(cell, boardSize, ctx, 1.f, Player::Nought);
            }

            std::vector<int> numberOfCasesPossessedByThePlayer;
            for (size_t i = 0; i < 2 * boardSize + 2; i++) {
                numberOfCasesPossessedByThePlayer.push_back(0);
            }
            for (CellIndex cell : playerCrossCells) {
                numberOfCasesPossessedByThePlayer[cell.x]++;             //colonne
                numberOfCasesPossessedByThePlayer[boardSize + cell.y]++; //ligne
                if (cell.x == cell.y) {
                    numberOfCasesPossessedByThePlayer[2 * boardSize]++; //diagonale haut gauche- bas droite
                }
                if (cell.x == static_cast<int>(boardSize - 1 - cell.y)) {
                    numberOfCasesPossessedByThePlayer[2 * boardSize + 1]++; //diagonale haut droite-bas gauche
                }
            }
            int compteur = 0;
            for (int numberOfCasesByRank : numberOfCasesPossessedByThePlayer) {
                //std::cout << "rank " << compteur << " " << numberOfCasesByRank << std::endl;
                compteur++;
                if (numberOfCasesByRank == static_cast<int>(boardSize)) {
                    std::cout << "cross wins" << std::endl;
                    game = false;
                    break;
                }
            }
        };

        ctx.mouse_pressed = [&](p6::MouseButton) {
            if (cellIsEmpty[hoveredCell->x][hoveredCell->y]) {
                cellIsEmpty[hoveredCell->x][hoveredCell->y] = false;
                switch (player) {
                case Player::Cross:
                    playerCrossCells.push_back({hoveredCell->x, hoveredCell->y});
                    break;
                case Player::Nought:
                    playerNoughtsCells.push_back({hoveredCell->x, hoveredCell->y});
                    break;
                }
                player = changePlayer(player);
            }
        };

        // Start the program
        ctx.start();
    }
    // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}