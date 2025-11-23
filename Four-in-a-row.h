#ifndef Four_in_a_row_H
#define Four_in_a_row_H

#include "BoardGame_Classes.h"
using namespace std;

class Four_in_a_row_Board : public Board<char> {
private:
    char blank_symbol = '.'; 
public:
    Four_in_a_row_Board();

    bool update_board(Move<char>* move)override;

    bool is_win(Player<char>* player)override;

    bool is_lose(Player<char>*)override { return false; };

    bool is_draw(Player<char>* player)override;

    bool game_is_over(Player<char>* player)override;
};


class Four_in_a_row_UI : public UI<char> {
public:
    Four_in_a_row_UI();

    ~Four_in_a_row_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type)override;

    virtual Move<char>* get_move(Player<char>* player)override;
};

#endif 
