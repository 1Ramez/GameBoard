#include <iostream>
#include <iomanip>
#include <cctype>
#include "word_Tic-Tac-Toe.h"

using namespace std;

//Board

void Word_Board::readDic(){
    ifstream dic("../../dic.txt");

    string word;
    while(dic >> word){
        words.insert(word);
    }

    dic.close();
}

Word_Board::Word_Board() : Board(3, 3) {
    for (auto& row : board){
        for (auto& cell : row){
            cell = blank_symbol;
        }
    }
    
    readDic();
}

bool Word_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char c = move->get_symbol();
    c = toupper(c);

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns || c < 'A' || c > 'Z' ) && (board[x][y] == blank_symbol) ){
        n_moves++;
        board[x][y] = c;
        return true;
    }
    return false;
}

bool Word_Board::is_win(Player<char>* player) {
    
    //Checking Rows
    for (int r = 0; r < 3; r++){
        string row = "";
        for (int c = 0; c < 3; c++){
            row += board[r][c];
        }
        string reversed_row = row;
        reverse(reversed_row.begin(), reversed_row.end());
        if (words.count(row) || words.count(reversed_row)){
            return true;
        }
    }

    //Checking Columns
    for (int c = 0; c < 3; c++){
        string column = "";
        for (int r = 0; r < 3; r++){
            column += board[r][c];
        }
        string reversed_column = column;
        reverse(reversed_column.begin(), reversed_column.end());
        if (words.count(column) || words.count(reversed_column)){
            return true;
        }
    }

    //Checking main Diagonal
    string diagonal = "";
    for (int i = 0; i < 3; i++){
        diagonal += board[i][i];
    }
    string reversed_diagonal = diagonal;
    reverse(reversed_diagonal.begin(), reversed_diagonal.end());
    if (words.count(diagonal) || words.count(reversed_diagonal)){
        return true;
    }

    //Checking anti Diagonal
    string anti = "";
    for (int i = 0; i < 3; i++){
        anti += board[2-i][i];
    }
    string reversed_anti = anti;
    reverse(reversed_anti.begin(), reversed_anti.end());
    if (words.count(anti) || words.count(reversed_anti)){
        return true;
    }

    return false;
}

bool Word_Board::is_lose(Player<char>* player){
    return false;
}

bool Word_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Word_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


//UI

Word_UI::Word_UI() : UI<char>("Weclome to Word Tic-Tac-Toe Game", 3) {}

Player<char>* Word_UI::create_player(string& name, char symbol, PlayerType type) {

    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer") << " player: " << name << "\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Word_UI::get_move(Player<char>* player) {
    int x, y;
    char c;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2) and character (A to Z): ";
        cin >> x >> y >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //To ignore any input more than the required
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        c = (rand() % 26) + 'A';
    }
    return new Move<char>(x, y, c);
}

Player<char>** Word_UI::setup_players() {
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