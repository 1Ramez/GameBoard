#include "Pyramid_TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//=============================================================================
// Pyramid_Board Implementation
//=============================================================================

template <typename T>
Pyramid_Board<T>::Pyramid_Board() : Board<T>(3, 5) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            this->board[i][j] = static_cast<T>(' ');
        }
    }
}

template <typename T>
bool Pyramid_Board<T>::is_valid_position(int x, int y) {
    if (x < 0 || x >= 3 || y < 0 || y >= 5) return false;

    if (x == 0) return y == 2;           // Top: only middle column
    if (x == 1) return y >= 1 && y <= 3; // Middle: 3 cells
    if (x == 2) return true;              // Base: all 5 cells

    return false;
}

template <typename T>
bool Pyramid_Board<T>::update_board(Move<T>* move) {
    int x = move->get_x();
    int y = move->get_y();

    if (!is_valid_position(x, y)) {
        cout << "Invalid position! Not in pyramid structure.\n";
        return false;
    }

    if (this->board[x][y] != static_cast<T>(' ')) {
        cout << "Position already occupied!\n";
        return false;
    }

    this->board[x][y] = move->get_symbol();
    this->n_moves++;
    return true;
}

template <typename T>
bool Pyramid_Board<T>::check_win(T symbol) {
    // Check horizontal line in row 1
    if (this->board[1][1] == symbol &&
        this->board[1][2] == symbol &&
        this->board[1][3] == symbol) {
        return true;
    }

    // Check horizontal lines in row 2 (3 possible)
    for (int j = 0; j <= 2; j++) {
        if (this->board[2][j] == symbol &&
            this->board[2][j + 1] == symbol &&
            this->board[2][j + 2] == symbol) {
            return true;
        }
    }

    // Check vertical line (column 2)
    if (this->board[0][2] == symbol &&
        this->board[1][2] == symbol &&
        this->board[2][2] == symbol) {
        return true;
    }

    // Check diagonal: top to bottom-left
    if (this->board[0][2] == symbol &&
        this->board[1][1] == symbol &&
        this->board[2][0] == symbol) {
        return true;
    }

    // Check diagonal: top to bottom-right
    if (this->board[0][2] == symbol &&
        this->board[1][3] == symbol &&
        this->board[2][4] == symbol) {
        return true;
    }

    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_win(Player<T>* player) {
    return check_win(player->get_symbol());
}

template <typename T>
bool Pyramid_Board<T>::is_lose(Player<T>* player) {
    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_draw(Player<T>* player) {
    // Total valid cells: 1 + 3 + 5 = 9
    return (this->n_moves == 9 && !is_win(player));
}

template <typename T>
bool Pyramid_Board<T>::game_is_over(Player<T>* player) {
    return is_win(player) || is_draw(player);
}

//=============================================================================
// Pyramid_Player Implementation
//=============================================================================

template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol)
    : Player<T>(name, symbol, PlayerType::HUMAN) {}

//=============================================================================
// Pyramid_Random_Player Implementation
//=============================================================================

template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol)
    : Player<T>("Random Computer", symbol, PlayerType::COMPUTER) {}

//=============================================================================
// Pyramid_UI Implementation
//=============================================================================

template <typename T>
Pyramid_UI<T>::Pyramid_UI()
    : UI<T>("Welcome to Pyramid Tic-Tac-Toe!", 3) {}

template <typename T>
Move<T>* Pyramid_UI<T>::get_move(Player<T>* player) {
    int x, y;

    // Display the pyramid board first
    Pyramid_Board<T>* board = dynamic_cast<Pyramid_Board<T>*>(player->get_board_ptr());
    auto matrix = board->get_board_matrix();

    cout << "\n";
    cout << "        " << matrix[0][2] << "  \n";
    cout << "       --- \n";
    cout << "      " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3] << " \n";
    cout << "     -------\n";
    cout << "    " << matrix[2][0] << " " << matrix[2][1] << " "
        << matrix[2][2] << " " << matrix[2][3] << " " << matrix[2][4] << "\n";
    cout << "   -----------\n\n";

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << "), enter your move.\n";
        cout << "Positions:\n";
        cout << "  Row 0: column 2 only (top)\n";
        cout << "  Row 1: columns 1, 2, 3 (middle)\n";
        cout << "  Row 2: columns 0, 1, 2, 3, 4 (base)\n";
        cout << "Row: ";
        cin >> x;
        cout << "Column: ";
        cin >> y;
    }
    else {
        // Random computer player
        do {
            x = rand() % 3;
            if (x == 0) y = 2;
            else if (x == 1) y = 1 + rand() % 3;
            else y = rand() % 5;
        } while (matrix[x][y] != static_cast<T>(' '));

        cout << player->get_name() << " chose: (" << x << ", " << y << ")\n";
    }

    return new Move<T>(x, y, player->get_symbol());
}

template <typename T>
Player<T>* Pyramid_UI<T>::create_player(string& name, T symbol, PlayerType type) {
    if (type == PlayerType::HUMAN) {
        return new Pyramid_Player<T>(name, symbol);
    }
    else {
        return new Pyramid_Random_Player<T>(symbol);
    }
}

//=============================================================================
// Explicit Template Instantiation
//=============================================================================

template class Pyramid_Board<char>;
template class Pyramid_Player<char>;
template class Pyramid_Random_Player<char>;
template class Pyramid_UI<char>;
