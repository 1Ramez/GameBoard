#include <iostream>
#include <iomanip>
#include <cctype>
#include "XO_FivebyFive.h"

using namespace std;

XO_5x5_Board::XO_5x5_Board() : Board(5, 5) {
    for (auto& row : board){
        for (auto& cell : row){
            cell = blank_symbol;
        }
    }
}

bool XO_5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) && (board[x][y] == blank_symbol || mark == 0)){
        if (mark == 0){
            n_moves--;
            board[x][y] = blank_symbol;
        }else{
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool XO_5x5_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool XO_5x5_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool XO_5x5_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

XO_5x5_UI::XO_5x5_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char>* XO_5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_5x5_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

void XO_5x5_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;

    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n      ";
    cout << "0";
    for (int j = 1; j < cols; ++j)
        cout << "    " << j;
    cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width) << matrix[i][j] << " |";
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
    }
    cout << endl;
}
