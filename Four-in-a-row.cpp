
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "Four-in-a-row.h"
using namespace std;
Four_in_a_row_Board::Four_in_a_row_Board() : Board(6,7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
bool Four_in_a_row_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char sym = move->get_symbol();

    if (col < 0 || col >= columns) {
        return false; 
    }

    for (int row = rows - 1; row >= 0; --row) {
        if (board[row][col] == blank_symbol) {
            board[row][col] = sym;
            n_moves++;
            return true;
        }
    }
    return false;
}

bool Four_in_a_row_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
for(int i=0;i<rows;i++){
    for(int j=0;j<columns-3;j++){
        if(board[i][j]==sym && board[i][j+1]==sym && board[i][j+2]==sym && board[i][j+3]==sym){
            return true;
        }
    }
}
for(int j=0;j<columns;j++){
    for(int i=0;i<rows-3;i++){
        if(board[i][j]==sym && board[i+1][j]==sym && board[i+2][j]==sym && board[i+3][j]==sym){
            return true;
        }
    }
}
for(int i=0;i<rows-3;i++){
    for(int j=0;j<columns-3;j++){
        if(board[i][j]==sym && board[i+1][j+1]==sym && board[i+2][j+2]==sym && board[i+3][j+3]==sym){
            return true;
        }
    }
}
for(int i=3;i<rows;i++){
    for(int j=0;j<columns-3;j++){
        if(board[i][j]==sym && board[i-1][j+1]==sym && board[i-2][j+2]==sym && board[i-3][j+3]==sym){
            return true;
        }
    }
}
    return false;
}

bool Four_in_a_row_Board::is_draw(Player<char>* player) {
    return (n_moves == 6*7 && !is_win(player));
}

bool Four_in_a_row_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Four_in_a_row_UI::Four_in_a_row_UI() : UI<char>("Welcome to FCAI Four-in-a-row Game ", 3) {}

Player<char>* Four_in_a_row_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Four_in_a_row_UI::get_move(Player<char>* player) {
    int y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move (0->6)  ";
        cin >>  y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(0, y, player->get_symbol());
}

