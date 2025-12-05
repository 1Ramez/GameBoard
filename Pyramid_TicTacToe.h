#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

using namespace std;

class Pyramid_Board : public Board<char> {
public:
    Pyramid_Board();
    bool is_valid_position(int row, int col);
    bool update_board(Move<char>* move);
    bool check_three_in_line(char symbol);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Pyramid_UI : public UI<char> {
public:
    Pyramid_UI();
    ~Pyramid_UI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
    Player<char>** setup_players();
};

#endif