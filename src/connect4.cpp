#include "connect4.hpp"
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"
#include "boardGame.hpp"
#include "playerSymbols.hpp"

//create a vector of "width of board" empty columns (represented by empty vectors of Players)
std::vector<std::vector<Player>> prepareEmptyColumns(BoardSize boardSize)
{
    std::vector<Player>              column;
    std::vector<std::vector<Player>> board;
    for (size_t x = 0; x < boardSize.w; x++) {
        board.push_back(column);
    }
    return board;
}

// Draw a cross or a nought in each cells that had been taken by a player
void drawBoardSymbols(std::vector<std::vector<Player>> board, BoardSize boardSize, p6::Context& ctx)
{
    for (size_t x = 0; x < board.size(); x++) {
        for (size_t y = 0; y < board[x].size(); y++) {
            drawPlayerSymbol({static_cast<int>(x), static_cast<int>(boardSize.h) - 1 - static_cast<int>(y)},
                             boardSize, ctx, 1.f, board[x][y]);
        }
    }
}

// true if the board is full
bool isBoardFull(std::vector<std::vector<Player>> board, BoardSize boardSize)
{
    int fullColumns = 0;
    for (std::vector<Player> column : board) {
        if (column.size() == boardSize.h) {
            fullColumns++;
        }
    }
    if (fullColumns == static_cast<int>(boardSize.w)) {
        return true;
    }
    else {
        return false;
    }
}

// Check that we are not out of range : if there is nothing in the row in a column because the column is too small
bool theRowExistsInThisColumn(std::vector<std::vector<Player>> board, CellIndex lastTry, int cellChecked)
{
    return board[cellChecked].size() > static_cast<size_t>(lastTry.y);
}

// Check if the last cell tried ends the game (if the player wins) and return the player if he actually wins
std::optional<Player> findWinner(std::vector<std::vector<Player>> board, CellIndex lastTry)
{
    Player currentPlayer = board[lastTry.x][lastTry.y];
    //column victory
    int score       = 0;
    int cellChecked = lastTry.y;
    // Count cells owned by the player in the column, with an index under the cell he tried, until a cell that he doesn't own is found
    while (cellChecked >= 0 && board[lastTry.x][cellChecked] == currentPlayer) {
        score++;
        cellChecked--;
    }
    cellChecked = lastTry.y + 1;
    // Count cells owned by the player in the column, with an index above the cell he tried, until a cell that he doesn't own is found
    while (cellChecked < static_cast<int>(board[lastTry.x].size()) && board[lastTry.x][cellChecked] == currentPlayer) {
        score++;
        cellChecked++;
    }
    if (score >= 4) {
        return currentPlayer;
    }

    //row victory
    score       = 0;
    cellChecked = lastTry.x;
    // Count cases owned by the player in the row, with an index under the case he tried, until a case that he doesn't own is found
    while (cellChecked >= 0 && theRowExistsInThisColumn(board, lastTry, cellChecked) && board[cellChecked][lastTry.y] == currentPlayer) {
        score++;
        cellChecked--;
    }
    cellChecked = lastTry.x + 1;
    // Count cases owned by the player in the row, with an index above the case he tried, until a case that he doesn't own is found
    while (cellChecked < static_cast<int>(board.size()) && theRowExistsInThisColumn(board, lastTry, cellChecked) && board[cellChecked][lastTry.y] == currentPlayer) {
        score++;
        cellChecked++;
    }
    if (score >= 4) {
        return currentPlayer;
    }

    //no victory
    return std::nullopt;
}

// return the first empty case or nullopt if the column is full
std::optional<CellIndex> findTheFirstEmptyCaseInTheColumn(int hoveredColumn, size_t boardHeight, int alreadyTakenCases)
{
    CellIndex positionTried = {hoveredColumn, static_cast<int>(boardHeight - 1 - alreadyTakenCases)};
    if (positionTried.y >= 0) { // The column is not full.
        return positionTried;
    }
    else {
        return std::nullopt;
    }
}

// We have the y to draw (which is a decreasing index) and we want the index in the array representing the board (which increases when we add something)
CellIndex flipYOfCell(CellIndex cell, size_t boardHeight)
{
    return {cell.x, static_cast<int>(boardHeight) - 1 - cell.y};
}

void playConnect4()
{
    try {
        // Create the Context by giving the initial size and name of our window
        int                              height        = 1200;
        int                              width         = 800;
        auto                             ctx           = p6::Context{{height, width, "Connect 4"}};
        BoardSize                        boardSize     = {7, 6};
        Player                           player        = Player::Cross;
        std::optional<int>               hoveredColumn = std::nullopt;
        std::optional<CellIndex>         positionTried = std::nullopt;
        bool                             game          = true;
        std::vector<std::vector<Player>> board         = prepareEmptyColumns(boardSize);
        std::optional<Player>            winner        = std::nullopt;

        // Define the update function. It will be called repeatedly.
        ctx.update = [&]() {
            if (game) {
                drawRectangleBoard(boardSize, ctx);
                drawBoardSymbols(board, boardSize, ctx);
                hoveredColumn = findHoveredColumn(ctx.mouse(), boardSize, ctx);
                if (hoveredColumn) {
                    positionTried = findTheFirstEmptyCaseInTheColumn(*hoveredColumn, static_cast<int>(boardSize.h), static_cast<int>(board[*hoveredColumn].size()));
                    drawPlayerSymbol(*positionTried, boardSize, ctx, 0.5f, player);
                }
                else {
                    positionTried = std::nullopt;
                }
            }
            else {
                drawWinner(boardSize, winner, ctx);
            }

            ctx.mouse_pressed = [&](p6::MouseButton) {
                if (!game) {
                    ctx.stop();
                }

                if (positionTried && hoveredColumn) {
                    CellIndex tryCoordinates = flipYOfCell(*positionTried, boardSize.h);
                    board[*hoveredColumn].push_back(player);
                    winner = findWinner(board, tryCoordinates);
                    if (winner) {
                        game = false;
                    }
                    player = changePlayer(player);
                }
                if (isBoardFull(board, boardSize)) {
                    game = false;
                }
            };
        };

        // Start the program
        ctx.start();
    }
    // Log any error that might occur
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}