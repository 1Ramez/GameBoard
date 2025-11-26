#pragma once
#ifndef INFINITY_XO_CLASSES_H
#define INFINITY_XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <queue>   // For tracking oldest moves
using namespace std;

/**
 * @class Infinity_Board
 * @brief Represents the Infinity Tic-Tac-Toe game board.
 * After every 3 moves, the oldest mark is removed.
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';        ///< Character used for empty cell
    queue<pair<int, int>> moveQueue;///< Keeps track of move order

public:
    /// @brief Construct a 3x3 Infinity Tic-Tac-Toe board.
    Infinity_Board();

    /// @brief Update board with player move or remove oldest if needed.
    bool update_board(Move<char>* move) override;

    /// @brief Check if player has 3 in a row.
    bool is_win(Player<char>* player) override;

    /// @brief Not used (no lose condition for this game).
    bool is_lose(Player<char>*) override { return false; }

    /// @brief Check if board is full (draw).
    bool is_draw(Player<char>* player) override;

    /// @brief Game is over if someone wins or it�s a draw.
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Infinity_UI
 * @brief Handles user input and output for Infinity Tic-Tac-Toe.
 */
class Infinity_UI : public UI<char> {
public:
    /// @brief Constructor displaying welcome message.
    Infinity_UI();

    /// @brief Destructor.
    ~Infinity_UI() {}

    /// @brief Create player based on name and type.
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /// @brief Get the next move from a player.
    Move<char>* get_move(Player<char>* player) override;
};

#endif // INFINITY_XO_CLASSES_H