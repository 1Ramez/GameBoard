#ifndef NUMERICAL_H
#define NUMERICAL_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <set>
using namespace std;

/**
 * @class Numerical_Board
 * @brief Implements a 3x3 Numerical Tic‑Tac‑Toe board.
 *
 * This board allows players to place unique numbers (odd for Player 1,
 * even for Player 2). A player wins when any row, column, or diagonal
 * sums to 15.
 */
class Numerical_Board : public Board<int> {
private:
    int blank_symbol = 0;              /**< Represents an empty board cell */
    set<int> used_numbers;             /**< Tracks numbers already used on the board */

public:
    /**
     * @brief Constructs a 3x3 numerical board and initializes all cells to blank.
     */
    Numerical_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move object containing x, y, and the number.
     * @return True if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<int>* move) override;

    /**
     * @brief Checks whether the given player has achieved a winning condition.
     * @param player Pointer to the player.
     * @return True if a row, column, or diagonal sums to 15.
     */
    bool is_win(Player<int>* player) override;

    /**
     * @brief Numerical Tic‑Tac‑Toe does not use loss conditions.
     * @return Always false.
     */
    bool is_lose(Player<int>*) override { return false; }

    /**
     * @brief Checks if the game is a draw (board full and no winner).
     * @param player Pointer to the player.
     * @return True if draw, false otherwise.
     */
    bool is_draw(Player<int>* player) override;

    /**
     * @brief Determines whether the game is over.
     * @param player Pointer to the player.
     * @return True if a win or draw occurred.
     */
    bool game_is_over(Player<int>* player) override;

    /**
     * @brief Validates whether a number can be placed by a specific player.
     * @param num The number the player wants to use.
     * @param player Pointer to the player.
     * @return True if valid (odd for Player1, even for Player2, not previously used).
     */
    bool is_valid_number(int num, Player<int>* player) const;

    /**
     * @brief Checks if a number has been used on the board.
     * @param num The number to check.
     * @return True if the number has already been used.
     */
    bool number_used(int num) const { return used_numbers.count(num) > 0; }
};

/**
 * @class Numerical_UI
 * @brief Handles user interaction for Numerical Tic‑Tac‑Toe.
 *
 * This class creates players and receives moves from either
 * human or computer players.
 */
class Numerical_UI : public UI<int> {
public:
    /**
     * @brief Constructs the UI with a welcome message.
     */
    Numerical_UI();

    /**
     * @brief Creates a player with a given name, symbol, and type.
     * @param name Reference to player's name.
     * @param symbol 1 for odd‑number player, 2 for even‑number player.
     * @param type HUMAN or COMPUTER.
     * @return Pointer to the created player.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

    /**
     * @brief Obtains a move from the player.
     * @param player Pointer to the player.
     * @return Pointer to a Move object containing chosen position and number.
     */
    Move<int>* get_move(Player<int>* player) override;
};

#endif // NUMERICAL_H
