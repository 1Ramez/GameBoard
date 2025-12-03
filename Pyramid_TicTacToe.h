#ifndef _PYRAMID_TICTACTOE_H
#define _PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"

/**
 * @brief Pyramid Tic-Tac-Toe Board Implementation
 *
 * Board structure:
 * Row 0: 1 cell (top)
 * Row 1: 3 cells (middle)
 * Row 2: 5 cells (base)
 */
template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool update_board(Move<T>* move) override;
    bool is_win(Player<T>* player) override;
    bool is_lose(Player<T>* player) override;
    bool is_draw(Player<T>* player) override;
    bool game_is_over(Player<T>* player) override;

private:
    bool check_win(T symbol);
    bool is_valid_position(int x, int y);
};

/**
 * @brief Human Player for Pyramid Tic-Tac-Toe
 */
template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol);
};

/**
 * @brief Computer Player for Pyramid Tic-Tac-Toe
 */
template <typename T>
class Pyramid_Random_Player : public Player<T> {
public:
    Pyramid_Random_Player(T symbol);
};

/**
 * @brief UI for Pyramid Tic-Tac-Toe
 */
template <typename T>
class Pyramid_UI : public UI<T> {
public:
    Pyramid_UI();
    Move<T>* get_move(Player<T>* player) override;
    Player<T>* create_player(string& name, T symbol, PlayerType type) override;
};

#endif // _PYRAMID_TICTACTOE_H