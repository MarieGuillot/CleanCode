#include "noughtsAndCrosses.hpp"
#include <math.h>
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"
#include "boardGame.hpp"
#include "playerSymbols.hpp"

// create a vector (same length than a column of the board) of vectors (representing the lines) of bool
// There is a bool for each cell and it is "true" if the cell is empty
// so basically return boardSize*boardSize "true" (board is a square)
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

// show the board : 1 when cell is empty and 0 if there is a cross or a nought
void showBoard(const std::vector<std::vector<bool>>& board, const size_t boardSize)
{
    for (size_t i = 0; i < boardSize; i++) {
        std::cout << "Line n°" << i << " : ";
        for (size_t j = 0; j < boardSize; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// create a vector with one cell for each column/line/diagonal (8 cells for a 3*3 board)
// each cell contains the number of cases possessed by the player in the given column/line/diagonal
// return true if for one cell, the number is equal to boardSize (i.e. you completed a column/line/diagonal = you win)
bool doesThePlayerWin(std::vector<CellIndex> playerCells, size_t boardSize)
{
    std::vector<int> numberOfCasesPossessedByThePlayer;
    for (size_t i = 0; i < 2 * boardSize + 2; i++) {
        numberOfCasesPossessedByThePlayer.push_back(0);
    }
    for (CellIndex cell : playerCells) {
        numberOfCasesPossessedByThePlayer[cell.x]++;             // column
        numberOfCasesPossessedByThePlayer[boardSize + cell.y]++; //line
        if (cell.x == cell.y) {
            numberOfCasesPossessedByThePlayer[2 * boardSize]++; //diagonal up left - bottom right
        }
        if (cell.x == static_cast<int>(boardSize - 1 - cell.y)) {
            numberOfCasesPossessedByThePlayer[2 * boardSize + 1]++; //diagonal up right - bottom left
        }
    }

    if (std::any_of(numberOfCasesPossessedByThePlayer.cbegin(), numberOfCasesPossessedByThePlayer.cend(),
                    [boardSize](int number) { return number == static_cast<int>(boardSize); })) {
        return true;
    }
    return false;
}

// return true if the board is full : false if there is at least one cell empty
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

// stop the game if someone wins (and tell who is the winner (variable winner))
// or stop the game if the board is full (no winner)
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

void playNoughtsAndCrosses()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int                            height      = 900;
        int                            width       = 900;
        auto                           ctx         = p6::Context{{height, width, "Nought And Crosses"}};
        BoardSize                      boardSize   = {3, 3};
        Player                         player      = Player::Cross; //player 1 takes Crosses, player 2 takes Noughts
        std::vector<std::vector<bool>> cellIsEmpty = createEmptyBoard(boardSize.w);
        //showBoard(cellIsEmpty, boardSize.w);
        std::vector<CellIndex>   playerCrossCells;
        std::vector<CellIndex>   playerNoughtsCells;
        std::optional<CellIndex> hoveredCell = std::nullopt;
        bool                     game        = true;
        std::optional<Player>    winner      = std::nullopt;

        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            if (game) {
                ctx.background({0.f, 0.f, 0.f, 1.f});
                drawRectangleBoard(boardSize, ctx);
                hoveredCell = findHoveredCell(ctx.mouse(), boardSize, ctx);
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

                checkIfTheGameIsFinished(player, game, winner, playerCrossCells, playerNoughtsCells, cellIsEmpty, boardSize.w);

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