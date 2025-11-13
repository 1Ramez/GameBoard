#ifndef NUMERICAL_H
#define NUMERICAL_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>
#include <set>
using namespace std;

class Numerical_Board : public Board<int> {
private:
    int blank_symbol = 0;
    set<int> used_numbers;
public:
    Numerical_Board();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>*) override { return false; }
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    bool is_valid_number(int num, Player<int>* player) const;
    bool number_used(int num) const { return used_numbers.count(num) > 0; }
};

class Numerical_UI : public UI<int> {
public:
    Numerical_UI();
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;
    Move<int>* get_move(Player<int>* player) override;
};
#endif // NUMERICAL_H    