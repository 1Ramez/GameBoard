#ifndef XO_FIVEBYFIVE_H
#define XO_FIVEBYFIVE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class XO_5x5_Board
 * @brief Represents the board logic for the 5x5 Tic-Tac-Toe game.
 *
 * This class implements a 5×5 board where players attempt to create as many
 * 3-in-a-row patterns as possible. At the end of the game (when the board is full),
 * the player with the higher number of scoring lines wins.
 */
class XO_5x5_Board : public Board<char> {
private:
    char blank_symbol = ' ';   /**< Character used for empty cells. */
    int p1_score = 0;          /**< Player 1’s total number of 3-in-a-row scores. */
    int p2_score = 0;          /**< Player 2’s total number of 3-in-a-row scores. */
    string p1_name;            /**< Name of first player. */
    string p2_name;            /**< Name of second player. */

public:
    /**
     * @brief Constructs an empty 5×5 board initialized with blank symbols.
     */
    XO_5x5_Board();

    /**
     * @brief Applies a player's move to the board.
     *
     * @param move Pointer to a Move object containing (x, y, symbol).
     * @return True if the move is valid and successfully applied; false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Determines if the specified player has won the game.
     *
     * A win is determined at the end of the game: the player with the higher number
     * of 3-in-a-row lines is declared the winner.
     *
     * @param player Pointer to the player being evaluated.
     * @return True if this player wins; false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Determines whether the specified player has lost the game.
     *
     * A loss occurs when the opponent has a higher score at the end of the game.
     *
     * @param player Pointer to the player to evaluate.
     * @return True if this player has lost; false otherwise.
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks whether the game ended in a draw.
     *
     * A draw occurs when 24 cells are filled and both players have equal scores.
     *
     * @param player Unused parameter (required by framework).
     * @return True if the game is a draw; false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks whether the game is over.
     *
     * For this game mode, the game ends when 24 cells are filled.
     *
     * @param player Unused parameter.
     * @return True when 24 cells are filled; false otherwise.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class XO_5x5_UI
 * @brief User interface handler for the 5x5 Tic-Tac-Toe game.
 *
 * This class manages player creation, move input, and board display
 * for both human and computer players.
 */
class XO_5x5_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI object and sets menu text and allowed retries.
     */
    XO_5x5_UI();

    /**
     * @brief Virtual destructor.
     */
    ~XO_5x5_UI() {}

    /**
     * @brief Creates a player object.
     *
     * @param name The player's display name.
     * @param symbol The character symbol assigned to the player ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to the newly created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Obtains a move from the current player.
     *
     * Human players are prompted to enter coordinates.
     * Computer players generate random legal moves.
     *
     * @param player Pointer to the player making the move.
     * @return Pointer to a newly allocated Move object.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Creates and returns the two game players.
     *
     * Handles asking for names and selecting player type.
     *
     * @return A dynamically allocated array of two Player pointers.
     */
    Player<char>** setup_players();

    /**
     * @brief Displays the board grid in a formatted manner.
     *
     * @param matrix 2D vector representing the current board state.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const;
};

#endif