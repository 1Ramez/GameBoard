#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"
using namespace std;

class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; 
    int score_S ;
    int score_U ;
    vector<vector<int>> move_order;
    int lastx;
    int lasty;

public:
    SUS_Board();
    bool update_board(Move<char>* move)override;

    bool is_win(Player<char>* player)override;

    bool is_lose(Player<char>*)override;

    bool is_draw(Player<char>* player)override;

    bool game_is_over(Player<char>* player)override;
    int calculate_score(char symbol);
};


class SUS_UI : public UI<char> {
public:
    SUS_UI();

    ~SUS_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type)override;
    virtual Move<char>* get_move(Player<char>* player)override;
    Player<char>** setup_players()override;
};

#endif 
