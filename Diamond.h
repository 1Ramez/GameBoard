#ifndef DIAMOND_H
#define DIAMOND_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
using namespace std;

class Diamond_Board : public Board<char> {
private:
    char blank_symbol = ' ';
    bool allowed[7][7] = {
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,1,1,1,1,1,0},
        {1,1,1,1,1,1,1},
        {0,1,1,1,1,1,0},
        {0,0,1,1,1,0,0},
        {0,0,0,1,0,0,0}
    };

public:
    Diamond_Board();

    // Board interface
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // helpers for UI/AI
    bool is_allowed(int row, int coulmen) const { return allowed[row][coulmen]; }
    int playable_count() const;

    vector<pair<int,int>> available_positions() const;
    char get_blank_symbol() const { return blank_symbol; }
};

class Diamond_UI : public UI<char> {
public:
    Diamond_UI();
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // DIAMOND_H
