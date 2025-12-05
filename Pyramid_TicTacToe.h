#ifndef _PYRAMID_TICTACTOE_H
#define _PYRAMID_TICTACTOE_H

#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board : public Board<T> {
public:
    Pyramid_Board();
    bool is_valid_position(int row, int col);
    bool update_board(Move<T>* move) override;
    bool check_three_in_line(T symbol);
    bool is_win(Player<T>* player) override;
    bool is_lose(Player<T>* player) override;
    bool is_draw(Player<T>* player) override;
    bool game_is_over(Player<T>* player) override;
};

template <typename T>
class Pyramid_HumanPlayer : public Player<T> {
public:
    Pyramid_HumanPlayer(string name, T symbol);
};

template <typename T>
class Pyramid_RandomPlayer : public Player<T> {
public:
    Pyramid_RandomPlayer(string name, T symbol);
};

template <typename T>
class Pyramid_UI : public UI<T> {
public:
    Pyramid_UI();
    Move<T>* get_move(Player<T>* player) override;
    Player<T>* create_player(string& name, T symbol, PlayerType type) override;
};

#endif