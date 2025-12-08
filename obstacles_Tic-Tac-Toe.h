#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Obstacles_Board
 * @brief Implements a 6x6 Tic-Tac-Toe variant with obstacles.
 *
 * In this version of the game, players place X and O on a 6×6 grid.
 * When Player O places a symbol, two obstacles ('#') are randomly added
 * to the board in empty positions.
 *
 * A player wins whenever they form a sequence of four consecutive symbols
 * horizontally, vertically, or diagonally.
 */
class Obstacles_Board : public Board<char> {
private:
    char blank_symbol = ' ';   /**< Character representing an empty cell. */
    char obstacle_symbol = '#';/**< Character representing an obstacle. */

    /**
     * @brief Randomly places one obstacle on an empty cell.
     *
     * This function selects a random position on the board and places
     * an obstacle symbol ('#') as long as the cell is empty.
     */
    void addObstacle();

public:
    /**
     * @brief Constructs an empty 6×6 board.
     *
     * Initializes all cells to blank symbols.
     */
    Obstacles_Board();

    /**
     * @brief Updates the board with a player's move.
     *
     * If Player O plays a move, the board automatically adds two obstacles.
     *
     * @param move Pointer to a Move object containing (x, y, symbol).
     * @return True if the move is valid and applied; false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks whether the specified player has won.
     *
     * A win occurs if the player forms four consecutive symbols in:
     *  - any row,
     *  - any column,
     *  - the main diagonal direction,
     *  - the anti-diagonal direction.
     *
     * @param player Pointer to the player being evaluated.
     * @return True if the player wins; false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief The game does not use loss conditions explicitly.
     * @param player Pointer to the player.
     * @return Always false.
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks if the game is a draw.
     *
     * A draw occurs when all 36 cells are filled and no player has won.
     *
     * @param player Pointer to the player.
     * @return True if the game ends in a draw; false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines whether the game is over.
     *
     * The game ends when a player wins or when the board is full.
     *
     * @param player Pointer to the player.
     * @return True if game over; false otherwise.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Obstacles_UI
 * @brief User interface for the Obstacles Tic-Tac-Toe game.
 *
 * This class manages creating players, receiving moves,
 * and printing the board for both human and computer players.
 */
class Obstacles_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI with a welcome message and retry settings.
     */
    Obstacles_UI();

    /**
     * @brief Virtual destructor.
     */
    ~Obstacles_UI() {}

    /**
     * @brief Creates a new player.
     *
     * @param name Player's chosen display name.
     * @param symbol Character assigned to the player ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to the newly created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Obtains a move from the player.
     *
     * Human players enter (x, y).
     * Computer players choose random valid coordinates.
     *
     * @param player Pointer to the player making the move.
     * @return Pointer to a new Move object representing the move.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Creates and initializes both players.
     *
     * Prompts the user to enter player names and select player types.
     * Assigns:
     *   - Player 1 → 'X'
     *   - Player 2 → 'O'
     *
     * @return A dynamic array of two Player pointers.
     *         Caller is responsible for deleting them.
     */
    Player<char>** setup_players();

    /**
     * @brief Displays the current board in a formatted style.
     *
     * @param matrix The board as a 2D vector of characters.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const;
};

#endif