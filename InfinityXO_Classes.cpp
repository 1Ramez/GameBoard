#include "InfinityXO_Classes.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

//-------------------------------------------------------------
// Infinity_Board Implementation
//-------------------------------------------------------------
Infinity_Board::Infinity_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    srand(time(0));
}

bool Infinity_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = toupper(move->get_symbol());

    // Validate position
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false; // already taken

    // Place mark
    board[x][y] = sym;
    n_moves++;
    moveQueue.push({ x, y });

    // After every 6 moves, remove the oldest
    if (n_moves > 6) {
        auto oldest = moveQueue.front();
        moveQueue.pop();
        board[oldest.first][oldest.second] = blank_symbol;
        n_moves--; // one mark removed
    }

    return true;
}

bool Infinity_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == sym && b == sym && c == sym;
        };

    // Rows and columns
    for (int i = 0; i < 3; ++i) {
        if (all_equal(board[i][0], board[i][1], board[i][2]) ||
            all_equal(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    // Diagonals
    if (all_equal(board[0][0], board[1][1], board[2][2]) ||
        all_equal(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool Infinity_Board::is_draw(Player<char>* player) {
    // Draw when no win and all cells filled (rare in this version)
    for (auto& row : board)
        for (auto& c : row)
            if (c == blank_symbol)
                return false;
    return !is_win(player);
}

bool Infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//-------------------------------------------------------------
// Infinity_UI Implementation
//-------------------------------------------------------------
Infinity_UI::Infinity_UI()
    : UI<char>("Welcome to Infinity Tic-Tac-Toe!", 3) {}

Player<char>* Infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << ((type == PlayerType::HUMAN) ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Infinity_UI::get_move(Player<char>* player) {
    int x, y;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << ", enter your move (x y): ";
        cin >> x >> y;
    }
    else {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        cout << player->get_name() << " (Computer) chose: " << x << " " << y << "\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}