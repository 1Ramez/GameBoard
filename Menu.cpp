#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "Numerical.h"
#include "Misere.h"
#include "Four-in-a-row.h"
#include "XO_FivebyFive.h"
#include "InfinityXO_Classes.h"
#include "FourByFour_Classes.h"
#include "SUS.h"
#include "Pyramid_TicTacToe.h"
#include "Diamond.h"
using namespace std;

void play_Numerical_TicTacToe(){
    Numerical_UI* ui = new Numerical_UI();
    Numerical_Board* board = new Numerical_Board();

    Player<int>** players = new Player<int>*[2];
    string name1, name2;
    string type_choice;

    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "1: Human, 2: Computer: ";
    cin >> type_choice;
    players[0] = ui->create_player(name1, 1, type_choice == "1" ? PlayerType::HUMAN : PlayerType::COMPUTER);

    cout << "Enter Player 2 name: ";
    cin >> name2;
    cout << "1: Human, 2: Computer: ";
    cin >> type_choice;
    players[1] = ui->create_player(name2, 2, type_choice == "1" ? PlayerType::HUMAN : PlayerType::COMPUTER);

    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);
    GameManager<int> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete board;
    delete ui;
}

void play_Misere_TicTacToe(){
    UI<char>* ui = new Misere_UI();
    Board<char>* xo_board = new Misere_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> Misere_game(xo_board, players, ui);

    Misere_game.run();

    delete xo_board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Four_in_a_row_TicTacToe(){ 
    UI<char>* game_ui = new Four_in_a_row_UI();
    Board<char>* xo_board = new Four_in_a_row_Board();

    Player<char>** players = game_ui->setup_players();

    GameManager<char> four_in_a_row_game(xo_board, players, game_ui);

    four_in_a_row_game.run();

    delete xo_board;
    for (int i = 0; i < 2; ++i){
        delete players[i];
    }
    delete[] players;
}

void play_5x5_TicTacToe(){
    UI<char>* game_ui = new XO_5x5_UI();
    Board<char>* xo_board = new XO_5x5_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> x_o_game(xo_board, players, game_ui);
    x_o_game.run();

    delete xo_board;
    for (int i = 0; i < 2; ++i){
        delete players[i];
    }
    delete[] players;
}

void play_Infinity_TicTacToe(){
    UI<char>* ui = new Infinity_UI();
    Board<char>* board = new Infinity_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_4x4_TicTacToe(){
    UI<char>* ui = new FourByFour_UI();
    Board<char>* board = new FourByFour_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_SUS_TicTacToe(){
    UI<char>* ui = new SUS_UI();
    Board<char>* board = new SUS_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_word_TicTacToe(){

}
void play_Pyramid_TicTacToe(){
     Pyramid_UI<char> ui;
     Player<char>** players = ui.setup_players();
     Pyramid_Board<char> board;
     GameManager<char> game(&board, players, &ui);
     game.run();
     delete players[0]; delete players[1]; delete[] players;

}

void play_Diamond_TicTacToe(){
    UI<char>* ui = new Diamond_UI();

    Board<char>* board = new Diamond_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}


int main(){
    srand(static_cast<unsigned int>(time(0)));

    string choice;
    while(true){
        cout << "-------------Games Menu---------------\n";
        cout << "| 1     Numerical Tic-Tac-Toe        |\n";
        cout << "| 2       Misere Tic-Tac-Toe         |\n";
        cout << "| 3        Four-in-a-row             |\n";
        cout << "| 4       5x5 Tic-Tac-Toe            |\n";
        cout << "| 5     Infinity Tic-Tac-Toe         |\n";
        cout << "| 6       4x4 Tic-Tac-Toe            |\n";
        cout << "| 7       SUS Tic-Tac-Toe            |\n";
        cout << "| 8       Word Tic-Tac-Toe           |\n";
        cout << "| 9      Pyramid Tic-Tac-Toe         |\n";
        cout << "| 10     Diamond Tic-Tac-Toe         |\n";
        cout << "| 0            EXIT                  |\n";
        cout << "--------------------------------------\n";

        cout << "\nSelect your Game: ";
        cin >> choice;

        if (choice == "0"){
            break;
        }else if (choice == "1"){
            play_Numerical_TicTacToe();

        }else if (choice == "2"){
            play_Misere_TicTacToe();

        }else if (choice == "3"){
            play_Four_in_a_row_TicTacToe();

        }else if (choice == "4"){
            play_5x5_TicTacToe();

        }else if (choice == "5"){
            play_Infinity_TicTacToe();

        }else if (choice == "6"){
            play_4x4_TicTacToe();
            
        }else if (choice == "7"){
            play_SUS_TicTacToe();

        }else if (choice == "8"){
            play_word_TicTacToe();

        }else if (choice == "9"){
            play_Pyramid_TicTacToe();

        }else if (choice == "10"){
            play_Diamond_TicTacToe();
        }else{
            cout << "Invalid option! Please try again.\n";
            continue;
        } 
    }
    
    return 0;
}