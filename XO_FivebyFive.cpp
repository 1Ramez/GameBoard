#include <iostream>
#include <iomanip>
#include <cctype>
#include "XO_FivebyFive.h"

using namespace std;

//Board

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
    char sym = player->get_symbol();
    int score = 0;

    //Rows
    for (int r = 0; r < 5; r++){
        for (int c = 0; c < 3; c++){
            if (board[r][c] == sym && board[r][c+1] == sym && board[r][c+2] == sym){
                score++;
            }
        }    
    }

    //Columns
    for (int c = 0; c < 5; c++){
        for (int r = 0; r < 3; r++){
            if (board[r][c] == sym && board[r+1][c] == sym && board[r+2][c] == sym){
                score++;
            }
        }
    }

    //Diagonals
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            if (board[r][c] == sym && board[r+1][c+1] == sym && board[r+2][c+2] == sym){
                score++;
            }
        }  
    }

    //Opposite Diagonals
    for (int r = 0; r < 3; r++){
        for (int c = 2; c < 5; c++){
            if (board[r][c] == sym && board[r+1][c-1] == sym && board[r+2][c-2] == sym){
                score++;
            }
        }    
    }

    //Recording scores
    if (sym == 'X'){
        p1_score = score;
    }else{
        p2_score = score;
    }

    if(n_moves == 24 && p2_score > p1_score){
        return true;
    }

    return false;
}

bool XO_5x5_Board::is_lose(Player<char>* player){
    if (n_moves == 24 && p1_score > p2_score){
        return true;
    }
    
    return false;
}

bool XO_5x5_Board::is_draw(Player<char>* player) {
    return (n_moves == 24 && p1_score == p2_score);
}

bool XO_5x5_Board::game_is_over(Player<char>* player) {
    return (n_moves == 24);
}


//UI

XO_5x5_UI::XO_5x5_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe", 3) {}

Player<char>* XO_5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer") << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_5x5_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 4): ";
        cin >> x >> y;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //To ignore any input more than the required
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

Player<char>** XO_5x5_UI::setup_players() {
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