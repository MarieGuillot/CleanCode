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

struct Coordinates {
    float x;
    float y;
};

Coordinates convertIntoWindowCoordinates(int x, int y, size_t boardSize)
{
    float       windowX           = p6::map<float>(static_cast<float>(x), 0.f, static_cast<float>(boardSize), -1.f, 1.f);
    float       windowY           = p6::map<float>(static_cast<float>(y), 0.f, static_cast<float>(boardSize), 1.f, -1.f);
    Coordinates WindowCoordinates = {windowX, windowY};
    return WindowCoordinates;
}

Player changePlayer(Player player)
{
    return static_cast<Player>((static_cast<int>(player) + 1) % 2);
}

void drawASquareAtIndex(CellIndex cell, size_t boardSize, p6::Context& ctx)
{
    Coordinates coordinates = convertIntoWindowCoordinates(cell.x, cell.y, boardSize);
    ctx.square(p6::TopLeftCorner{coordinates.x, coordinates.y}, 1.f / static_cast<float>(boardSize));
}

float colorOfIndex(int x, size_t boardSize)
{
    return 1.f / static_cast<float>(boardSize) * static_cast<float>(x);
}

p6::Color colorOfPosition(int x, int y, size_t boardSize)
{
    const float red  = colorOfIndex(static_cast<int>(x), boardSize);
    const float blue = colorOfIndex(static_cast<int>(y), boardSize);
    return p6::Color{red, 1.f, blue, 1.f};
}

void drawNoughtAtIndex(CellIndex cell, size_t boardSize, p6::Context& ctx, float alphaColor)
{
    Coordinates coordinates    = convertIntoWindowCoordinates(cell.x, cell.y, boardSize);
    const float halfSideOfCell = 1.f / boardSize;
    ctx.fill                   = p6::Color{1.f, 1.f, 1.f, alphaColor};
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
    ctx.fill = p6::Color{1.f, 1.f, 1.f, 1.f};
    ctx.circle(p6::Center{0.f, 0.f},
               p6::Radius{0.8f});
    ctx.fill = backgroundColor;
    ctx.circle(p6::Center{0.f, 0.f},
               p6::Radius{0.5f});
}

void drawCrossAtIndex(const CellIndex cell, size_t boardSize, p6::Context& ctx, float alphaColor)
{
    Coordinates coordinates    = convertIntoWindowCoordinates(cell.x, cell.y, boardSize);
    const float halfSideOfCell = 1.f / boardSize;
    ctx.fill                   = p6::Color{1.f, 1.f, 1.f, alphaColor};
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
    ctx.fill      = p6::Color{1.f, 1.f, 1.f, 1.f};
    auto rotation = p6::Angle(p6::Radians(M_PI / 4.));
    ctx.rectangle(p6::Center{0.f, 0.f},
                  p6::Radii(0.2f, 0.8f),
                  rotation);
    ctx.rectangle(p6::Center{0.f, 0.f},
                  p6::Radii(0.2f, 0.8f),
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
            p6::Color color         = colorOfPosition(x, y, boardSize);
            ctx.fill                = color;
            ctx.use_stroke          = false;
            Coordinates coordinates = convertIntoWindowCoordinates(x, y, boardSize);
            ctx.square(p6::TopLeftCorner{coordinates.x, coordinates.y}, 1.f / static_cast<float>(boardSize));
        }
    }
}

CellIndex convertIntoBoardCoordinates(float x, float y, size_t boardSize)
{
    float     boardX           = p6::map<float>(static_cast<float>(x), -1.f, 1.f, 0.f, static_cast<float>(boardSize));
    float     boardY           = p6::map<float>(static_cast<float>(y), 1.f, -1.f, 0.f, static_cast<float>(boardSize));
    CellIndex boardCoordinates = {static_cast<int>(boardX), static_cast<int>(boardY)};
    return boardCoordinates;
}

std::optional<CellIndex> findHoveredCell(glm::vec2 mouse, size_t boardSize)
{
    if (mouse.x >= -1 && mouse.x <= 1 && mouse.y >= -1 && mouse.y <= 1) {
        return convertIntoBoardCoordinates(mouse.x, mouse.y, boardSize);
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

bool doesThePlayerWin(std::vector<CellIndex> playerCells, size_t boardSize)
{
    std::vector<int> numberOfCasesPossessedByThePlayer;
    for (size_t i = 0; i < 2 * boardSize + 2; i++) {
        numberOfCasesPossessedByThePlayer.push_back(0);
    }
    for (CellIndex cell : playerCells) {
        numberOfCasesPossessedByThePlayer[cell.x]++;             //colonne
        numberOfCasesPossessedByThePlayer[boardSize + cell.y]++; //ligne
        if (cell.x == cell.y) {
            numberOfCasesPossessedByThePlayer[2 * boardSize]++; //diagonale haut gauche- bas droite
        }
        if (cell.x == static_cast<int>(boardSize - 1 - cell.y)) {
            numberOfCasesPossessedByThePlayer[2 * boardSize + 1]++; //diagonale haut droite-bas gauche
        }
    }

    if (std::any_of(numberOfCasesPossessedByThePlayer.cbegin(), numberOfCasesPossessedByThePlayer.cend(), [boardSize](int number) { return number == static_cast<int>(boardSize); })) {
        return true;
    }
    return false;
}

bool boardIsFull(std::vector<std::vector<bool>> board, const size_t boardSize)
{
    for (size_t i = 0; i < boardSize; i++) {
        for (size_t j = 0; j < boardSize; j++) {
            if (board[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

void checkIfTheGameIsFinished(Player player, bool& game, std::optional<Player>& winner, const std::vector<CellIndex>& playerCrossCells, const std::vector<CellIndex>& playerNoughtsCells, const std::vector<std::vector<bool>>& cellIsEmpty, size_t boardSize)
{
    switch (player) {
    case Player::Cross:
        game = !doesThePlayerWin(playerCrossCells, boardSize);
        break;
    case Player::Nought:
        game = !doesThePlayerWin(playerNoughtsCells, boardSize);
        break;
    }
    if (game == false) {
        winner = player;
    }

    if (boardIsFull(cellIsEmpty, boardSize)) {
        game = false;
    }
}

void drawWinner(size_t boardSize, std::optional<Player> winner, p6::Context& ctx)
{
    p6::Color backgroundColor = colorOfPosition(boardSize / 2, boardSize / 2, boardSize);

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
        //showBoard(cellIsEmpty, boardSize);
        std::vector<CellIndex>   playerCrossCells;
        std::vector<CellIndex>   playerNoughtsCells;
        std::optional<CellIndex> hoveredCell = std::nullopt;
        bool                     game        = true;
        std::optional<Player>    winner      = std::nullopt;

        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            // Clear the objects that were drawn during the previous update

            if (game) {
                drawBoard(boardSize, ctx);
                hoveredCell = findHoveredCell(ctx.mouse(), boardSize);
                if (hoveredCell) {
                    drawPlayerSymbol(*hoveredCell, boardSize, ctx, 0.5f, player);
                }

                for (CellIndex cell : playerCrossCells) {
                    drawPlayerSymbol(cell, boardSize, ctx, 1.f, Player::Cross);
                }
                for (CellIndex cell : playerNoughtsCells) {
                    drawPlayerSymbol(cell, boardSize, ctx, 1.f, Player::Nought);
                }
            }
            else {
                drawWinner(boardSize, winner, ctx);
            }
        };

        ctx.mouse_pressed = [&](p6::MouseButton) {
            if (!game) {
                ctx.stop();
            }

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

                checkIfTheGameIsFinished(player, game, winner, playerCrossCells, playerNoughtsCells, cellIsEmpty, boardSize);

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