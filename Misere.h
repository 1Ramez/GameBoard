#ifndef MISERE_H
#define MISERE_H
#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;

/**
 * @class Misere_Board
 * @brief Implements the board logic for Misere (Reverse) Tic-Tac-Toe.
 *
 * In Misere Tic-Tac-Toe, players try *not* to make a 3-in-a-row.
 * The first player who forms a winning line actually **loses**.
 *
 * Board size is 3×3, and the game ends when:
 * - A player forms a 3-in-a-row (they lose).
 * - All 9 cells are filled with no losing lines (draw).
 */
class Misere_Board : public Board<char> {
public:
    /**
     * @brief Constructs an empty 3×3 Misere Tic-Tac-Toe board.
     *
     * Initializes all cells to spaces (' ').
     */
    Misere_Board();

    /**
     * @brief Applies a move to the Misere board.
     *
     * Checks bounds and ensures the cell is empty.
     *
     * @param move Pointer to the Move<char> object.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the specified player **wins**.
     *
     * In Misere rules, a player wins if the *opponent* loses.
     * A losing condition occurs when the opponent forms a 3-in-a-row.
     *
     * @param player Pointer to the current player.
     * @return true if the player wins, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the specified player **loses**.
     *
     * A player loses immediately if they form a 3-in-a-row horizontally,
     * vertically, or diagonally.
     *
     * @param player Pointer to the player being evaluated.
     * @return true if this player loses, false otherwise.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks for a draw.
     *
     * A draw occurs when all 9 moves are played, and
     * no losing line is formed by either player.
     *
     * @param player Not used (required by interface).
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines whether the game has ended.
     *
     * Game ends if:
     * - A player loses,
     * - A player wins,
     * - Or a draw occurs.
     *
     * @param player Pointer to the player who made the move.
     * @return true if the game is over, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};


/**
 * @class Misere_UI
 * @brief Handles user interaction for the Misere Tic-Tac-Toe game.
 *
 * Responsible for:
 * - Creating players,
 * - Getting moves from human or computer,
 * - Displaying prompts.
 */
class Misere_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Misere game UI.
     *
     * Sets the welcome message and the number of retries for invalid inputs.
     */
    Misere_UI();

    /**
     * @brief Creates a player (human or computer).
     *
     * @param name The player's display name.
     * @param symbol Symbol assigned to the player ('X' or 'O').
     * @param type Human or Computer.
     * @return Pointer to a newly created Player<char>.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Obtains a move from the player.
     *
     * Human players enter (row, col).
     * Computer players choose a random valid position.
     *
     * @param player Pointer to the player making the move.
     * @return Pointer to a new Move<char> object.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif
