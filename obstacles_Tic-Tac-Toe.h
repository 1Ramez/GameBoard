#ifndef OBSTACLES_TIC_TAC_TOE_H
#define OBSTACLES_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

class Obstacles_Board : public Board<char> {
private:
    char blank_symbol = ' ';
    char obstacle_symbol = '#';

    void addObstacle();

public:
    Obstacles_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>* player);
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
};

class Obstacles_UI : public UI<char> {
public:
    Obstacles_UI();
    ~Obstacles_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players();

    void display_board_matrix(const vector<vector<char>>& matrix) const;
};

#endif