#ifndef FOURBYFOUR_CLASSES_H
#define FOURBYFOUR_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

class FourByFour_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    FourByFour_Board();

    bool update_board(Move<char>* move) override;
    bool move_token(int from_x, int from_y, int to_x, int to_y);

    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class FourByFour_UI : public UI<char> {
public:
    FourByFour_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif // FOURBYFOUR_CLASSES_H