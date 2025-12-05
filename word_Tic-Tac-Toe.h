#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <set>
#include <fstream>

using namespace std;

/**
 * @class Word_Board
 * @brief Implements the board and logic for the Word Tic-Tac-Toe game.
 *
 * This variant of Tic-Tac-Toe uses a 3×3 grid. Players place letters (A–Z)
 * instead of X/O, attempting to form valid 3-letter dictionary words.
 * A player wins immediately when a valid word is formed horizontally,
 * vertically, or diagonally (in either forward or reverse order).
 */
class Word_Board : public Board<char> {
private:
    char blank_symbol = ' ';          /**< Character used to represent empty cells. */
    set<string> words;                /**< Dictionary of valid 3-letter words. */

    /**
     * @brief Loads the dictionary from a text file.
     *
     * Reads a list of valid 3-letter English words into the @ref words set.
     * Expected file name: `dic.txt`.
     */
    void readDic();

public:
    /**
     * @brief Constructs an empty 3×3 Word Tic-Tac-Toe board.
     *
     * Initializes all board cells to blank and loads the dictionary.
     */
    Word_Board();

    /**
     * @brief Applies a player's move to the board.
     *
     * A move is valid only if the target cell is empty and the character is a letter A–Z.
     *
     * @param move Pointer to the Move containing (x, y, character).
     * @return True if the move is valid and successfully placed.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks whether the specified player has formed a valid word.
     *
     * The check is performed for all rows, columns, main diagonal, and anti-diagonal.
     * Words are matched in both forward and reversed order.
     *
     * @param player Pointer to the player being evaluated.
     * @return True if this player forms any valid word; otherwise false.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Determines whether the player has lost.
     *
     * For this game mode, losing is not explicitly used.
     *
     * @param player Pointer to the player to evaluate.
     * @return Always returns false.
     */
    bool is_lose(Player<char>*);

    /**
     * @brief Checks whether the game ended in a draw.
     *
     * A draw occurs when the board is full and no valid word is formed.
     *
     * @param player Unused; required by the framework.
     * @return True if the board is full and no player wins.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines whether the game has ended.
     *
     * The game ends when a player forms a word or when the board is full.
     *
     * @param player Pointer to the current player.
     * @return True if the game is won or drawn.
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Word_UI
 * @brief Handles user interaction for the Word Tic-Tac-Toe game.
 *
 * Provides functions to create players, request moves, and configure
 * player types (Human or Computer).
 */
class Word_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Word Tic-Tac-Toe UI.
     *
     * Sets the welcome message and input retry limit.
     */
    Word_UI();

    /**
     * @brief Virtual destructor.
     */
    ~Word_UI() {};

    /**
     * @brief Creates a new player.
     *
     * @param name The player's chosen display name.
     * @param symbol Character symbol assigned to the player (Not used in this game).
     * @param type Whether the player is Human or Computer.
     * @return Pointer to the newly allocated Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Obtains a move from the given player.
     *
     * Human players are prompted for (x, y, letter).
     * Computer players generate random coordinates and a random letter A–Z.
     *
     * @param player Pointer to the player making the move.
     * @return Pointer to a newly created Move object containing (x, y, character).
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Creates and initializes the two game players.
     *
     * Handles name input and selection of player type.
     *
     * @return A dynamic array of two Player pointers.
     */
    Player<char>** setup_players();
};

#endif