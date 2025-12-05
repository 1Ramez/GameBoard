/**
 * @file FourByFour_Classes.h
 * @brief Header file for 4x4 Tic-Tac-Toe game implementation
 */

#ifndef FOURBYFOUR_CLASSES_H
#define FOURBYFOUR_CLASSES_H

#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class FourByFour_Board
 * @brief Represents a 4x4 Tic-Tac-Toe board with token movement mechanics
 */
class FourByFour_Board : public Board<char> {
private:
    char blank_symbol = '.';
    
public:
    /**
     * @brief Constructor that initializes a 4x4 board
     */
    FourByFour_Board();
    
    /**
     * @brief Updates the board with a player's move
     * @param move Pointer to the Move object
     * @return true if successful, false otherwise
     */
    bool update_board(Move<char>* move) override;
    
    /**
     * @brief Moves a token from one position to another
     * @param from_x Source row index
     * @param from_y Source column index
     * @param to_x Destination row index
     * @param to_y Destination column index
     * @return true if successful, false otherwise
     */
    bool move_token(int from_x, int from_y, int to_x, int to_y);
    
    /**
     * @brief Checks if the given player has won
     * @param player Pointer to the Player object
     * @return true if won, false otherwise
     */
    bool is_win(Player<char>* player) override;
    
    /**
     * @brief Checks if the given player has lost
     * @param player Pointer to the Player object
     * @return true if lost, false otherwise
     */
    bool is_lose(Player<char>* player) override;
    
    /**
     * @brief Checks if the game ended in a draw
     * @param player Pointer to the Player object
     * @return true if draw, false otherwise
     */
    bool is_draw(Player<char>* player) override;
    
    /**
     * @brief Checks if the game is over
     * @param player Pointer to the Player object
     * @return true if game over, false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class FourByFour_UI
 * @brief User interface handler for 4x4 Tic-Tac-Toe game
 */
class FourByFour_UI : public UI<char> {
public:
    /**
     * @brief Constructor that displays welcome message
     */
    FourByFour_UI();
    
    /**
     * @brief Creates a player object based on type
     * @param name Reference to the player's name
     * @param symbol The player's symbol
     * @param type The type of player
     * @return Pointer to the created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    
    /**
     * @brief Gets the next move from a player
     * @param player Pointer to the Player object
     * @return Pointer to a Move object
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FOURBYFOUR_CLASSES_H