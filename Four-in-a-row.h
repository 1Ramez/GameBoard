#ifndef Four_in_a_row_H
#define Four_in_a_row_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Four_in_a_row_Board
 * @brief Represents the board for the Four-in-a-row (Connect 4) game.
 *
 * This variant of Tic-Tac-Toe uses a 6x7 grid. Players drop discs into columns
 * A player wins immediately when a four-in-a-row is formed horizontally,
 * vertically, or diagonally 
 */
class Four_in_a_row_Board : public Board<char> {
private:
    /**
     * @brief The symbol used to represent an empty cell on the board.
     */
    char blank_symbol = '.';

public:
    /**
     * @brief Constructs an empty 6x7 Four-in-a-row board and initializes all cells to blank.
     */
    Four_in_a_row_Board();

    /**
     * @brief Places a move onto the board.
     *
     * The move contains the target column and the player's symbol.
     * The function inserts the disc into the lowest available row in the column.
     *
     * @param move Pointer to the Move<char> object.
     * @return true if the move is valid and applied, false if the column is full or invalid.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the given player has won.
     *
     * A win occurs if the player has four of their symbols in a row
     * horizontally, vertically, or diagonally.
     *
     * @param player Pointer to the player to check for victory.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Always false for this game.
     *
     * Losing is simply the opponent winning; no separate lose condition exists.
     *
     * @return false always.
     */
    bool is_lose(Player<char>*) override { return false; };

    /**
     * @brief Checks if the game ended in a draw.
     *
     * A draw occurs if the board is full and no player has won.
     *
     * @param player Not used, but required for overriding.
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game has ended either by win or draw.
     *
     * @param player Pointer to the player making the move.
     * @return true if the game is over, false otherwise.
     */
    bool game_is_over(Player<char>* player) override;
};


/**
 * @class Four_in_a_row_UI
 * @brief Handles interaction with the user for the Four-in-a-row game.
 *
 * This includes creating players and receiving moves from human or computer players.
 */
class Four_in_a_row_UI : public UI<char> {
public:
    /**
     * @brief Constructs the user interface for the Four-in-a-row game.
     * Sets a welcome message and cell display width.
     */
    Four_in_a_row_UI();

    /**
     * @brief Destructor for the UI class.
     */
    ~Four_in_a_row_UI() {};

    /**
     * @brief Creates a new player (human or computer).
     *
     * @param name Player's name.
     * @param symbol Symbol representing the player ('X' or 'O').
     * @param type Enum that indicates if the player is HUMAN or COMPUTER.
     * @return Pointer to a newly created Player<char>.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the specified player.
     *
     * If the player is human, input is taken from standard input.
     * If the player is computer, a column is selected automatically.
     *
     * @param player Pointer to the player whose move is being requested.
     * @return Pointer to a newly created Move<char> object representing the player's move.
     */
    virtual Move<char>* get_move(Player<char>* player) override;     
    };

#endif
