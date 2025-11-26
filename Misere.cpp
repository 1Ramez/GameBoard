#include "Misere.h"
#include <iostream>
using namespace std;

Misere_Board::Misere_Board() : Board<char>(3,3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char Sym = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3)
        return false;
    if (board[x][y] != ' ')
        return false;

    board[x][y] = Sym;
    n_moves++;
    return true;
}

bool Misere_Board::is_lose(Player<char>* player) {
    char Sym = player->get_symbol();

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == Sym && board[i][1] == Sym && board[i][2] == Sym)
            return true;
        if (board[0][i] == Sym && board[1][i] == Sym && board[2][i] == Sym)
            return true;
    }
    if (board[0][0] == Sym && board[1][1] == Sym && board[2][2] == Sym)
        return true;
    if (board[0][2] == Sym && board[1][1] == Sym && board[2][0] == Sym)
        return true;

    return false;
}

bool Misere_Board::is_win(Player<char>* player) {
    Player<char>* other = (player->get_symbol() == 'X')
        ? new Player<char>("tmp",'O',PlayerType::HUMAN)
        : new Player<char>("tmp",'X',PlayerType::HUMAN);

    bool result = is_lose(other);
    delete other;
    return result;
}

bool Misere_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_lose(player));
}

bool Misere_Board::game_is_over(Player<char>* player) {
    return is_lose(player) || is_win(player) || is_draw(player);
}

Misere_UI::Misere_UI()
    : UI<char>("Welcome to FCAI Misere (Reverse) Tic-Tac-Toe!", 3) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_UI::get_move(Player<char>* player) {
    Misere_Board* board = static_cast<Misere_Board*>(player->get_board_ptr());
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " please enter row and col: ";
        cin >> x >> y;

        return new Move<char>(x, y, player->get_symbol());
    }
    else 
    {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board->get_board_matrix()[x][y] != ' ');

        cout << player->get_name() << " (Computer) played at: "
             << x << " " << y << endl;

        return new Move<char>(x, y, player->get_symbol());
    }
}
