#include "SUS.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
SUS_Board::SUS_Board() : Board(3,3),move_order(3,vector<int>(3,0)) {
   score_S = 0;
   score_U = 0;
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char sym = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns||board[x][y] != blank_symbol) {
        return false; 
    }

int s_before = calculate_score('S');
int u_before = calculate_score('U');
board[x][y] = sym;
n_moves++;
lastx = x;
lasty = y;
int s_after = calculate_score('S');
int u_after = calculate_score('U');
int gain=0;
if(sym=='S')
gain=s_after - s_before;
else if(sym=='U')
gain=u_after - u_before;
if(gain>0){
    if(sym=='S')
    score_S += gain;
    else if(sym=='U')
    score_U += gain;
}
cout<<"Score S: "<<score_S<<"\n Score U: "<<score_U<<endl;
    return true;
}

int SUS_Board::calculate_score(char symbol) {
    int cnt = 0;
     auto is_sus = [&](int a, int b, int c, int d, int e, int f) {
        return board[a][b] == 'S' &&
               board[c][d] == 'U' &&
               board[e][f] == 'S';
    };

    for (int r = 0; r < 3; r++)
        if (is_sus(r, 0, r, 1, r, 2)) cnt++;

    for (int c = 0; c < 3; c++)
        if (is_sus(0, c, 1, c, 2, c)) cnt++;

    if (is_sus(0, 0, 1, 1, 2, 2)) cnt++;

    if (is_sus(0, 2, 1, 1, 2, 0)) cnt++;
    return cnt;

}
bool SUS_Board::game_is_over(Player<char>* player) {
    return (n_moves == 9);
}

 bool SUS_Board::is_win(Player<char>* player) {
    if(n_moves!=9)return false;
    char sym = player->get_symbol();
    int player_score =(sym == 'S' ? score_S : score_U);
    int opponent_score = (sym == 'S' ? score_U : score_S);

    return (player_score > opponent_score);
}
bool SUS_Board::is_lose(Player<char>* player) {
    if (n_moves != 9) return false;

    char sym = player->get_symbol();
    int player_score = (sym == 'S' ? score_S : score_U);
    int opponent_score = (sym == 'S' ? score_U : score_S);
    return player_score < opponent_score;
}


bool SUS_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && score_S == score_U);
}
SUS_UI::SUS_UI():UI<char>("Welcome to FCAI SUS Game",3) {}
Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << " (" << player->get_symbol() << ") enter x y: ";
        cin >> x >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        x = rand() % 3;
        y = rand() % 3;
        cout << "Computer plays: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];

    string n1, n2;
    int t1, t2;

    cout << "Enter name for Player S: ";
    getline(cin >> ws, n1);

    cout << "Human(1) or Computer(2)? ";
    cin >> t1;

    cout << "Enter name for Player U: ";
    getline(cin >> ws, n2);

    cout << "Human(1) or Computer(2)? ";
    cin >> t2;
    players[0] = create_player(n1, 'S', (t1 == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER));
    players[1] = create_player(n2, 'U', (t2 == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER));

    return players;
}