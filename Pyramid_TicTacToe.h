/**
 * @file Pyramid_TicTacToe.h
 * @brief Header file for Pyramid Tic-Tac-Toe game implementation
 */

#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class Pyramid_Board
 * @brief Represents a pyramid-shaped Tic-Tac-Toe board
 */
class Pyramid_Board : public Board<char> {
public:
    /**
     * @brief Constructor that initializes a 3x5 pyramid board
     */
    Pyramid_Board();
    
    /**
     * @brief Checks if a position is valid within the pyramid structure
     * @param row The row index
     * @param col The column index
     * @return true if valid, false otherwise
     */
    bool is_valid_position(int row, int col);
    
    /**
     * @brief Updates the board with a player's move
     * @param move Pointer to the Move object
     * @return true if successful, false otherwise
     */
    bool update_board(Move<char>* move);
    
    /**
     * @brief Checks if three marks of the given symbol are aligned
     * @param symbol The player's symbol
     * @return true if three in a row, false otherwise
     */
    bool check_three_in_line(char symbol);
    
    /**
     * @brief Checks if the given player has won
     * @param player Pointer to the Player object
     * @return true if won, false otherwise
     */
    bool is_win(Player<char>* player);
    
    /**
     * @brief Checks if the given player has lost
     * @param player Pointer to the Player object
     * @return Always returns false
     */
    bool is_lose(Player<char>* player);
    
    /**
     * @brief Checks if the game ended in a draw
     * @param player Pointer to the Player object
     * @return true if draw, false otherwise
     */
    bool is_draw(Player<char>* player);
    
    /**
     * @brief Checks if the game is over
     * @param player Pointer to the Player object
     * @return true if game over, false otherwise
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Pyramid_UI
 * @brief User interface handler for Pyramid Tic-Tac-Toe game
 */
class Pyramid_UI : public UI<char> {
public:
    /**
     * @brief Constructor that displays welcome message
     */
    Pyramid_UI();
    
    /**
     * @brief Destructor
     */
    ~Pyramid_UI() {}
    
    /**
     * @brief Creates a player object based on type
     * @param name Reference to the player's name
     * @param symbol The player's symbol
     * @param type The type of player
     * @return Pointer to the created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    
    /**
     * @brief Gets the next move from a player
     * @param player Pointer to the Player object
     * @return Pointer to a Move object
     */
    virtual Move<char>* get_move(Player<char>* player);
    
    /**
     * @brief Sets up both players for the game
     * @return Array of two Player pointers
     */
    Player<char>** setup_players();
};

#endif