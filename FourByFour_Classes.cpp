#include "FourByFour_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//--------------------------------------- FourByFour_Board
FourByFour_Board::FourByFour_Board() : Board(4, 4) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool FourByFour_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != blank_symbol)
        return false;
    board[x][y] = mark;
    n_moves++;
    return true;
}

bool FourByFour_Board::move_token(int from_x, int from_y, int to_x, int to_y) {
    if (from_x < 0 || from_x >= rows || from_y < 0 || from_y >= columns) return false;
    if (to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns) return false;
    if (board[to_x][to_y] != blank_symbol) return false;
    if (abs(from_x - to_x) + abs(from_y - to_y) != 1) return false;
    swap(board[from_x][from_y], board[to_x][to_y]);
    return true;
}

bool FourByFour_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    auto check_three = [&](int a1, int b1, int a2, int b2, int a3, int b3) {
        return board[a1][b1] == sym && board[a2][b2] == sym && board[a3][b3] == sym;
        };
    // rows
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 2;j++)
            if (check_three(i, j, i, j + 1, i, j + 2)) return true;
    // columns
    for (int j = 0;j < 4;j++)
        for (int i = 0;i < 2;i++)
            if (check_three(i, j, i + 1, j, i + 2, j)) return true;
    // diagonals
    for (int i = 0;i < 2;i++)
        for (int j = 0;j < 2;j++) {
            if (check_three(i, j, i + 1, j + 1, i + 2, j + 2)) return true;
            if (check_three(i + 2, j, i + 1, j + 1, i, j + 2)) return true;
        }
    return false;
}

bool FourByFour_Board::is_lose(Player<char>* player) { return false; }
bool FourByFour_Board::is_draw(Player<char>* player) { return n_moves == 16 && !is_win(player); }
bool FourByFour_Board::game_is_over(Player<char>* player) { return is_win(player) || is_draw(player); }

//--------------------------------------- FourByFour_UI
FourByFour_UI::FourByFour_UI() : UI<char>("Welcome to 4x4 Tic-Tac-Toe!", 1) {}

Player<char>* FourByFour_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* FourByFour_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter x y: ";
        cin >> x >> y;
    }
    else { // COMPUTER
        do {
            x = rand() % 4;
            y = rand() % 4;
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != '.');
        cout << player->get_name() << " (" << player->get_symbol() << ") moves to " << x << " " << y << "\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}