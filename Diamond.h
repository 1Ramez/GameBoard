#ifndef DIAMOND_H
#define DIAMOND_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

/**
 * @class Diamond_Board
 * @brief Represents the board for the Diamond Tic-Tac-Toe variant.
 *
 * This game uses a diamond-shaped 7×7 grid where only specific cells are playable.
 * Players aim to win by simultaneously forming a line of three and a line of four
 * in different directions (horizontal, vertical, or diagonal). The two lines may
 * share one common cell.
 *
 * Invalid (non-playable) cells are marked in the board and cannot be selected.
 */
class Diamond_Board : public Board<char> {
private:
    /**
     * @brief Symbol representing an empty playable cell.
     */
    char blank_symbol = ' ';

    /**
     * @brief Matrix defining which cells are playable (1) or blocked (0).
     *
     * The layout forms a diamond shape:
     * - Row 0 and 6: 1 playable cell
     * - Row 1 and 5: 3 playable cells
     * - Row 2 and 4: 5 playable cells
     * - Row 3: 7 playable cells
     */
    bool allowed[7][7] = {
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,1,1,1,1,1,0},
        {1,1,1,1,1,1,1},
        {0,1,1,1,1,1,0},
        {0,0,1,1,1,0,0},
        {0,0,0,1,0,0,0}
    };

public:
    /**
     * @brief Constructs and initializes a diamond-shaped 7×7 board.
     *
     * Playable cells are filled with blank symbols.
     * Blocked cells are pre-marked and cannot be used during the game.
     */
    Diamond_Board();

    /**
     * @brief Applies a move to the board if valid.
     *
     * A move is valid when:
     * - It is inside board bounds.
     * - The target cell is marked as playable.
     * - The cell is currently empty.
     *
     * @param move Pointer to the Move<char> containing coordinates and symbol.
     * @return true if the move is successfully applied; false otherwise.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks whether the player has satisfied the winning condition.
     *
     * A win occurs when the player has:
     * - A line of three symbols AND
     * - A line of four symbols,
     * both in different directions.
     *
     * Shared cells between the two lines are allowed.
     *
     * @param player Pointer to the player being evaluated.
     * @return true if the player satisfies the winning condition.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Always returns false.
     *
     * A losing condition is not directly tracked—losing simply means the opponent wins.
     *
     * @return false always.
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Checks whether the game has ended in a draw.
     *
     * A draw occurs when:
     * - All playable cells are filled AND
     * - No player has achieved the winning condition.
     *
     * @param player Not used, but required by the abstract interface.
     * @return true if the game ends in a draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over (either win or draw).
     *
     * @param player Pointer to the current player.
     * @return true if the game has ended.
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if a given position is playable according to the diamond layout.
     *
     * @param row Board row index.
     * @param coulmen Board column index.
     * @return true if the cell is playable, false otherwise.
     */
    bool is_allowed(int row, int coulmen) const { return allowed[row][coulmen]; }

    /**
     * @brief Counts the number of playable cells in the diamond grid.
     *
     * @return Total number of playable positions.
     */
    int playable_count() const;

    /**
     * @brief Retrieves all currently empty and playable board positions.
     *
     * @return A vector of (row, column) pairs indicating valid moves.
     */
    vector<pair<int,int>> available_positions() const;

    /**
     * @brief Returns the symbol used for empty playable cells.
     * @return The blank cell symbol.
     */
    char get_blank_symbol() const { return blank_symbol; }
};



/**
 * @class Diamond_UI
 * @brief Handles user interaction for the Diamond Tic-Tac-Toe game.
 *
 * This includes:
 * - Player creation (human/computer)
 * - Reading moves from players
 * - Displaying the diamond-shaped board
 */
class Diamond_UI : public UI<char> {
public:
    /**
     * @brief Constructs the UI with a welcome message and default settings.
     */
    Diamond_UI();

    /**
     * @brief Creates a player (human or computer) with a given name and symbol.
     *
     * @param name Player's display name.
     * @param symbol Character representing the player ('X' or 'O').
     * @param type Player type (HUMAN or COMPUTER).
     * @return Pointer to the newly created Player<char>.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from a player.
     *
     * - Human players enter row/column manually.
     * - Computer players randomly select a valid available position.
     *
     * @param player Pointer to the player taking a turn.
     * @return Pointer to a dynamically allocated Move<char> object.
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the full 7×7 board including blocked cells.
     *
     * Blocked cells remain visible so players understand the diamond shape.
     *
     * @param matrix 2D character matrix representing the board.
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // DIAMOND_H
