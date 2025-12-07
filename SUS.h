#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class SUS_Board
 * @brief A 3x3 board for the SUS scoring game.
 *
 * This game uses characters 'S' and 'U'.  
 * When the pattern (S U S) appears in any row, column, or diagonal,
 * it counts as 1 point.  
 *
 * The game ends when the board is full, and the player with the highest score wins.
 */
class SUS_Board : public Board<char> {
private:
    /**
     * @brief Symbol representing an empty cell.
     */
    char blank_symbol = '.';

    /**
     * @brief Total score accumulated by player 'S'.
     */
    int score_S;

    /**
     * @brief Total score accumulated by player 'U'.
     */
    int score_U;

    /**
     * @brief Keeps track of the order in which cells were played.
     */
    vector<vector<int>> move_order;

    /**
     * @brief Stores x-coordinate of the last move.
     */
    int lastx;

    /**
     * @brief Stores y-coordinate of the last move.
     */
    int lasty;

public:
    /**
     * @brief Constructs an empty SUS board and initializes scores.
     */
    SUS_Board();

    /**
     * @brief Applies a move if valid.
     *
     * Updates the board, recalculates scores, and counts the move.
     *
     * @param move Pointer to the move object.
     * @return true if move is valid, false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player wins after the board is full.
     *
     * A player wins if their score is greater than their opponent's.
     *
     * @param player Pointer to the player.
     * @return true if player wins, false otherwise.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player loses after the board is full.
     *
     * Losing means the opponent has a higher score.
     *
     * @param player Pointer to player.
     * @return true if player loses.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game ends in a draw.
     *
     * A draw occurs when both scores are equal and board is full.
     *
     * @param player Pointer to player.
     * @return true if draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended.
     *
     * The game ends when 9 moves are played.
     *
     * @param player Pointer to player.
     * @return true if game over.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Calculates number of SUS patterns currently on the board.
     *
     * Counts all occurrences of the pattern **S U S**
     * in rows, columns, and diagonals.
     *
     * @param symbol The symbol requesting score ('S' or 'U').
     * @return Number of SUS patterns.
     */
    int calculate_score(char symbol);
};


/**
 * @class SUS_UI
 * @brief Handles user input and player creation for the SUS game.
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructs a UI with a default welcome message.
     */
    SUS_UI();

    /**
     * @brief Default destructor.
     */
    ~SUS_UI() {};

    /**
     * @brief Creates a new player of type HUMAN or COMPUTER.
     *
     * @param name Player's name.
     * @param symbol 'S' or 'U'.
     * @param type PlayerType enum.
     * @return Pointer to created player.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from human or generates one for computer.
     *
     * @param player Pointer to active player.
     * @return Pointer to new Move<char>.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Creates two players: Player S and Player U.
     *
     * Asks user for their names and whether each is human or computer.
     *
     * @return Array of two Player pointers.
     */
    Player<char>** setup_players() override;
};

#endif
