#include <iostream>
#include <iomanip>
#include <limits>
#include "Pyramid_TicTacToe.h"

using namespace std;

Pyramid_Board::Pyramid_Board() : Board(3, 5) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (is_valid_position(i, j)) {
                board[i][j] = ' ';
            } else {
                board[i][j] = '#';
            }
        }
    }
}

bool Pyramid_Board::is_valid_position(int row, int col) {
    if (row < 0 || row >= 3 || col < 0 || col >= 5)
        return false;
    
    if (row == 0 && col == 2) return true;
    if (row == 1 && (col >= 1 && col <= 3)) return true;
    if (row == 2) return true;
    
    return false;
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (!is_valid_position(x, y)) {
        return false;
    }

    if (board[x][y] != ' ') {
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Pyramid_Board::check_three_in_line(char symbol) {
    if (board[1][1] == symbol && board[1][2] == symbol && board[1][3] == symbol)
        return true;

    if (board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[2][1] == symbol && board[2][2] == symbol && board[2][3] == symbol)
        return true;
    if (board[2][2] == symbol && board[2][3] == symbol && board[2][4] == symbol)
        return true;

    if (board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol)
        return true;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][3] == symbol && board[2][4] == symbol)
        return true;

    return false;
}


bool Pyramid_Board::is_win(Player<char>* player) {
    return check_three_in_line(player->get_symbol());
}

bool Pyramid_Board::is_lose(Player<char>* player) {
    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return (is_win(player) || is_draw(player));
}

Pyramid_UI::Pyramid_UI() : UI<char>("Welcome to Pyramid Tic-Tac-Toe", 3) {}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer") << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2) and (0 to 4): ";
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Pyramid_Board* board = dynamic_cast<Pyramid_Board*>(player->get_board_ptr());
        do {
            x = rand() % 3;
            y = rand() % 5;
        } while (!board->is_valid_position(x, y) || board->get_board_matrix()[x][y] != ' ');
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>** Pyramid_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player 1");
    PlayerType typeX = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameX, static_cast<char>('X'), typeX);

    string nameO = get_player_name("Player 2");
    PlayerType typeO = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameO, static_cast<char>('O'), typeO);

    return players;
}