#include "Diamond.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

Diamond_Board::Diamond_Board() : Board<char>(7,7) {
  
    for (int row = 0; row < 7; ++row) {
        for (int c = 0; c < 7; ++c) {
            if (allowed[row][c]) board[row][c] = blank_symbol;
            else board[row][c] = '@';
        }
    }
    n_moves = 0;
}

bool Diamond_Board::update_board(Move<char>* move) {
    int row = move->get_x();
    int c = move->get_y();
    char sym = move->get_symbol();

    if (row < 0 || row >= 7 || c < 0 || c >= 7) return false;
    if (!allowed[row][c]) return false;        
    if (board[row][c] != blank_symbol) return false; // occupied

    board[row][c] = toupper(sym);
    ++n_moves;
    return true;
}

vector<pair<int,int>> Diamond_Board::available_positions() const {
    vector<pair<int,int>> res;
    for (int row = 0; row < 7; ++row)
        for (int c = 0; c < 7; ++c)
            if (allowed[row][c] && board[row][c] == blank_symbol)
                res.push_back({row,c});
    return res;
}

int Diamond_Board::playable_count() const {
    int count = 0;
    for (int row=0;row<7;++row) for (int c=0;c<7;++c) if (allowed[row][c]) ++count;
    return count;
}

static bool line_has_len(const vector<char>& line, char sym, int target, bool require_exact=false) {
    int count = 0;
    for (char ch : line) {
        if (ch == sym) { ++count; if (count >= target) return true; }
        else count = 0;
    }
    return false;
}

bool Diamond_Board::is_win(Player<char>* player) {
    char sym = toupper(player->get_symbol());
    bool has3[4] = {false,false,false,false};
    bool has4[4] = {false,false,false,false};

    // Horizontal
    for (int row=0; row<7; ++row) {
        vector<char> line;
        for (int c=0;c<7;++c) if (allowed[row][c]) line.push_back(board[row][c]);
        if (!line.empty()) {
            if (line_has_len(line, sym, 3)) has3[0] = true;
            if (line_has_len(line, sym, 4)) has4[0] = true;
        }
    }
    // Vertical
    for (int c=0; c<7; ++c) {
        vector<char> line;
        for (int row=0;row<7;++row) if (allowed[row][c]) line.push_back(board[row][c]);
        if (!line.empty()) {
            if (line_has_len(line, sym, 3)) has3[1] = true;
            if (line_has_len(line, sym, 4)) has4[1] = true;
        }
    }

    // Diagonals 
    for (int diff = -6; diff <= 6; ++diff) {
        vector<char> line;
        for (int row=0;row<7;++row) {
            int c = row - diff;
            if (c < 0 || c >= 7) continue;
            if (allowed[row][c]) line.push_back(board[row][c]);
        }
        if (!line.empty()) {
            if (line_has_len(line, sym, 3)) has3[2] = true;
            if (line_has_len(line, sym, 4)) has4[2] = true;
        }
    }
    for (int sum = 0; sum <= 12; ++sum) {
        vector<char> line;
        for (int row=0;row<7;++row) {
            int c = sum - row;
            if (c < 0 || c >= 7) continue;
            if (allowed[row][c]) line.push_back(board[row][c]);
        }
        if (!line.empty()) {
            if (line_has_len(line, sym, 3)) has3[3] = true;
            if (line_has_len(line, sym, 4)) has4[3] = true;
        }
    }

    for (int d3 = 0; d3 < 4; ++d3) {
        if (!has3[d3]) continue;
        for (int d4 = 0; d4 < 4; ++d4) {
            if (d4 == d3) continue;
            if (has4[d4]) return true;
        }
    }

    return false;
}

bool Diamond_Board::is_draw(Player<char>* player) {
    int total = playable_count();
    return (n_moves >= total && !is_win(player));
}

bool Diamond_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Diamond_UI::Diamond_UI() : UI<char>("Welcome to Diamond Tic-Tac-Toe ", 3) {}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    Diamond_Board* b = static_cast<Diamond_Board*>(player->get_board_ptr());
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") please enter row and col : ";
       cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (x < 0 || x >= 7 || y < 0 || y >= 7 || !b->is_allowed(x,y) || b->get_board_matrix()[x][y] != b->get_blank_symbol()) {
            cout << "Invalid or occupied. Enter row and col again: ";
           cin >> x >> y;
        }
        return new Move<char>(x, y, player->get_symbol());
    } else {
        auto avail = b->available_positions();
        if (avail.empty()) return new Move<char>(0,0,player->get_symbol());
        int idx = rand() % avail.size();
        auto pr = avail[idx];
        cout << player->get_name() << " (Computer) played at: " << pr.first << " " << pr.second << "\n";
        return new Move<char>(pr.first, pr.second, player->get_symbol());
    }
}
void Diamond_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;
    int rows = matrix.size();
    int cols = matrix[0].size();

    cout << "\n      ";
    for (int j = 0; j < cols; ++j) {
        cout << setw(3) << j << " ";
    }
    cout << "\n   " << string((cell_width + 4) * cols, '-') << "\n";

    for (int i = 0; i < rows; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; ++j) {
            cout << " " << setw(2) << matrix[i][j] << " |";
        }
        cout << "\n   " << string((cell_width + 4) * cols, '-') << "\n";
    }
    cout << endl;
}
