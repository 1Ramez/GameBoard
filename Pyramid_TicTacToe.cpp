#include "Pyramid_TicTacToe.h"
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

template <typename T>
Pyramid_Board<T>::Pyramid_Board() : Board<T>(3, 5) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (is_valid_position(i, j)) {
                this->board[i][j] = ' ';
            } else {
                this->board[i][j] = '#';
            }
        }
    }
}

template <typename T>
bool Pyramid_Board<T>::is_valid_position(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 5)
        return false;
    
    if (row == 0 && col == 2) return true;
    if (row == 1 && (col >= 1 && col <= 3)) return true;
    if (row == 2) return true;
    
    return false;
}

template <typename T>
bool Pyramid_Board<T>::update_board(Move<T>* move) {
    int x = move->get_x();
    int y = move->get_y();
    T symbol = move->get_symbol();

    if (!is_valid_position(x, y)) {
        return false;
    }

    if (this->board[x][y] != ' ') {
        return false;
    }

    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}

template <typename T>
bool Pyramid_Board<T>::check_three_in_line(T symbol) {
    if (this->board[1][1] == symbol && this->board[1][2] == symbol && this->board[1][3] == symbol)
        return true;
    if (this->board[2][0] == symbol && this->board[2][1] == symbol && this->board[2][2] == symbol)
        return true;
    if (this->board[2][1] == symbol && this->board[2][2] == symbol && this->board[2][3] == symbol)
        return true;
    if (this->board[2][2] == symbol && this->board[2][3] == symbol && this->board[2][4] == symbol)
        return true;

    if (this->board[0][2] == symbol && this->board[1][2] == symbol && this->board[2][2] == symbol)
        return true;

    if (this->board[0][2] == symbol && this->board[1][1] == symbol && this->board[2][0] == symbol)
        return true;
    if (this->board[0][2] == symbol && this->board[1][3] == symbol && this->board[2][4] == symbol)
        return true;
    if (this->board[1][1] == symbol && this->board[2][2] == symbol && this->board[2][3] == symbol)
        return true;
    if (this->board[1][3] == symbol && this->board[2][2] == symbol && this->board[2][1] == symbol)
        return true;

    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_win(Player<T>* player) {
    return check_three_in_line(player->get_symbol());
}

template <typename T>
bool Pyramid_Board<T>::is_lose(Player<T>* player) {
    return false;
}

template <typename T>
bool Pyramid_Board<T>::is_draw(Player<T>* player) {
    if (this->n_moves >= 9) {
        if (is_win(player)) return false;
        return true;
    }
    return false;
}

template <typename T>
bool Pyramid_Board<T>::game_is_over(Player<T>* player) {
    return is_win(player) || is_draw(player);
}

template <typename T>
Pyramid_HumanPlayer<T>::Pyramid_HumanPlayer(string name, T symbol)
    : Player<T>(name, symbol, PlayerType::HUMAN) {}

template <typename T>
Pyramid_RandomPlayer<T>::Pyramid_RandomPlayer(string name, T symbol)
    : Player<T>(name, symbol, PlayerType::COMPUTER) {}

template <typename T>
Pyramid_UI<T>::Pyramid_UI() : UI<T>("=== Pyramid Tic-Tac-Toe ===", 3) {}

template <typename T>
Move<T>* Pyramid_UI<T>::get_move(Player<T>* player) {
    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Enter row and column (e.g., 0 2): ";
        cin >> x >> y;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return new Move<T>(-1, -1, player->get_symbol());
        }
        
        return new Move<T>(x, y, player->get_symbol());
    } else {
        Pyramid_Board<T>* board = dynamic_cast<Pyramid_Board<T>*>(player->get_board_ptr());
        vector<pair<int, int>> valid_moves;
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (board->is_valid_position(i, j)) {
                    auto matrix = board->get_board_matrix();
                    if (matrix[i][j] == ' ') {
                        valid_moves.push_back({i, j});
                    }
                }
            }
        }
        
        if (valid_moves.empty()) {
            return new Move<T>(-1, -1, player->get_symbol());
        }
        
        int random_index = rand() % valid_moves.size();
        auto move = valid_moves[random_index];
        
        cout << player->get_name() << " (Computer) plays: " 
             << move.first << " " << move.second << "\n";
        
        return new Move<T>(move.first, move.second, player->get_symbol());
    }
}

template <typename T>
Player<T>* Pyramid_UI<T>::create_player(string& name, T symbol, PlayerType type) {
    if (type == PlayerType::HUMAN) {
        return new Pyramid_HumanPlayer<T>(name, symbol);
    } else {
        return new Pyramid_RandomPlayer<T>(name, symbol);
    }
}

template class Pyramid_Board<char>;
template class Pyramid_HumanPlayer<char>;
template class Pyramid_RandomPlayer<char>;
template class Pyramid_UI<char>;