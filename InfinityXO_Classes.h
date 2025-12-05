/**
 * @file InfinityXO_Classes.h
 * @brief Header file for Infinity Tic-Tac-Toe game implementation
 */

#pragma once
#ifndef INFINITY_XO_CLASSES_H
#define INFINITY_XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <queue>

using namespace std;

/**
 * @class Infinity_Board
 * @brief Represents the Infinity Tic-Tac-Toe game board
 */
class Infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';
    queue<pair<int, int>> moveQueue;
    
public:
    /**
     * @brief Constructor that initializes a 3x3 Infinity board
     */
    Infinity_Board();
    
    /**
     * @brief Updates the board with a player's move
     * @param move Pointer to the Move object
     * @return true if successful, false otherwise
     */
    bool update_board(Move<char>* move) override;
    
    /**
     * @brief Checks if the given player has won
     * @param player Pointer to the Player object
     * @return true if won, false otherwise
     */
    bool is_win(Player<char>* player) override;
    
    /**
     * @brief Checks if the given player has lost
     * @param player Pointer to the Player object
     * @return Always returns false
     */
    bool is_lose(Player<char>*) override { return false; }
    
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
 * @class Infinity_UI
 * @brief User interface handler for Infinity Tic-Tac-Toe game
 */
class Infinity_UI : public UI<char> {
public:
    /**
     * @brief Constructor that displays welcome message
     */
    Infinity_UI();
    
    /**
     * @brief Destructor
     */
    ~Infinity_UI() {}
    
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

#endif // INFINITY_XO_CLASSES_H