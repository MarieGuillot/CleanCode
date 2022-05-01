#include "connect4.hpp"
#include <iostream>
#include "../lib/p6/include/p6/p6.h"
#include "board.hpp"
#include "boardGame.hpp"
#include "playerSymbols.hpp"

std::vector<std::vector<Player>> prepareEmptyColumns(BoardSize boardSize)
{
    std::vector<Player>              column;
    std::vector<std::vector<Player>> board;
    for (size_t x = 0; x < boardSize.w; x++) {
        board.push_back(column);
    }
    return board;
}

void drawBoardSymbols(std::vector<std::vector<Player>> board, BoardSize boardSize, p6::Context& ctx)
{
    for (size_t x = 0; x < board.size(); x++) {
        for (size_t y = 0; y < board[x].size(); y++) {
            drawPlayerSymbol({static_cast<int>(x), static_cast<int>(boardSize.h) - 1 - static_cast<int>(y)},
                             boardSize, ctx, 1.f, board[x][y]);
        }
    }
}

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

std::optional<Player> findWinner(std::vector<std::vector<Player>> board, CellIndex lastTry)
{
    Player currentPlayer = board[lastTry.x][lastTry.y];
    //column victory
    int score       = 0;
    int caseChecked = lastTry.y;
    while (caseChecked >= 0 && board[lastTry.x][caseChecked] == currentPlayer) {
        score++;
        caseChecked--;
    }
    caseChecked = lastTry.y + 1;
    while (caseChecked < static_cast<int>(board[lastTry.x].size()) && board[lastTry.x][caseChecked] == currentPlayer) {
        score++;
        caseChecked++;
    }
    if (score >= 4) {
        return currentPlayer;
    }

    //row victory
    score       = 0;
    caseChecked = lastTry.x;
    while (caseChecked >= 0 && board[caseChecked].size() > static_cast<size_t>(lastTry.y) && board[caseChecked][lastTry.y] == currentPlayer) {
        score++;
        caseChecked--;
    }
    caseChecked = lastTry.x + 1;
    while (caseChecked < static_cast<int>(board.size()) && board[caseChecked].size() > static_cast<size_t>(lastTry.y) && board[caseChecked][lastTry.y] == currentPlayer) {
        score++;
        caseChecked++;
    }
    if (score >= 4) {
        return currentPlayer;
    }

    return std::nullopt;
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
                // Clear the objects that were drawn during the previous update
                ctx.background({0.f, 0.f, 0.f});
                drawRectangleBoard(boardSize, ctx);
                drawBoardSymbols(board, boardSize, ctx);
                hoveredColumn = findHoveredColumn(ctx.mouse(), boardSize, ctx);
                if (hoveredColumn) {
                    positionTried = {*hoveredColumn, static_cast<int>(boardSize.h) - 1 - static_cast<int>(board[*hoveredColumn].size())};
                    drawPlayerSymbol(*positionTried, boardSize, ctx, 0.5f, player);
                }
                else {
                    positionTried = std::nullopt;
                }
            }
            else {
                //ctx.background({0.f, 0.f, 0.f});
                drawWinner(boardSize, winner, ctx);
            }

            ctx.mouse_pressed = [&](p6::MouseButton) {
                if (!game) {
                    ctx.stop();
                }

                if (positionTried && hoveredColumn) {
                    if (positionTried->y >= 0) {
                        CellIndex tryCoordinates = {*hoveredColumn, static_cast<int>(board[*hoveredColumn].size())};
                        board[*hoveredColumn].push_back(player);
                        winner = findWinner(board, tryCoordinates);
                        if (winner) {
                            game = false;
                        }
                        player = changePlayer(player);
                    }
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