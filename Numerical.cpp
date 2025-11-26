#include "Numerical.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
using namespace std;
Numerical_Board::Numerical_Board() : Board(3,3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

}
bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;

    if (board[x][y] != blank_symbol || used_numbers.count(num))
        return false;

    board[x][y] = num;
    used_numbers.insert(num);
    n_moves++;
    return true;
}
bool Numerical_Board::is_valid_number(int num, Player<int>* player) const {
    if (used_numbers.count(num))
        return false;

    // Player 1 uses odd numbers
    if (player->get_symbol() == 1)
        return (num % 2 == 1 && num >= 1 && num <= 9);
    else
        return (num % 2 == 0 && num >= 2 && num <= 8);
}


bool Numerical_Board::is_win(Player<int>* player) {
    // Check all rows, columns, and diagonals for sum == 15
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] && board[i][1] && board[i][2] &&
            board[i][0] + board[i][1] + board[i][2] == 15)
            return true;

        if (board[0][i] && board[1][i] && board[2][i] &&
            board[0][i] + board[1][i] + board[2][i] == 15)
            return true;
    }

    if (board[0][0] && board[1][1] && board[2][2] &&
        board[0][0] + board[1][1] + board[2][2] == 15)
        return true;

    if (board[0][2] && board[1][1] && board[2][0] &&
        board[0][2] + board[1][1] + board[2][0] == 15)
        return true;

    return false;
}
bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}


Numerical_UI::Numerical_UI() : UI<int>("Weclome to Numerical Tic-Tac-Toe", 3) {}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << (symbol == 1 ? " (Odd Numbers)" : " (Even Numbers)") << endl;

    return new Player<int>(name, symbol, type);
}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, num;
    Numerical_Board* board = static_cast<Numerical_Board*>(player->get_board_ptr());
    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " - Enter row, column, and number: ";
            cin >> x >> y >> num;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool flag = false;
    while (!flag) {
        if (!board->is_valid_number(num, player)) {
            cout << "Invalid number! Try again: ";
            cin >> x >> y >> num;
        } else if (x < 0 || x >= 3 || y < 0 || y >= 3 || board->get_board_matrix()[x][y] != 0) {
            cout << "Invalid position! Try again: ";
            cin >> x >> y >> num;
        } else {
            flag = true;
        }
    }
    } else if (player->get_type() == PlayerType::COMPUTER) {
        do {
            x = rand() % 3;
            y = rand() % 3;
            num = (player->get_symbol() == 1) ? (rand()%5)*2+1 : (rand()%4)*2+2;
        } while (!board->is_valid_number(num, player) || board->get_board_matrix()[x][y]!=0);
    }


    return new Move<int>(x, y, num);
}
