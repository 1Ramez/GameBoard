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
#include "word_Tic-Tac-Toe.h"
#include "obstacles_Tic-Tac-Toe.h"

using namespace std;

void play_Numerical_TicTacToe(){
    Numerical_UI* ui = new Numerical_UI();
    Numerical_Board* board = new Numerical_Board();

    Player<int>** players = ui->setup_players();
    
    GameManager<int> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Misere_TicTacToe(){
    UI<char>* ui = new Misere_UI();
    Board<char>* board = new Misere_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Four_in_a_row_TicTacToe(){ 
    UI<char>* ui = new Four_in_a_row_UI();
    Board<char>* board = new Four_in_a_row_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_5x5_TicTacToe(){
    UI<char>* ui = new XO_5x5_UI();
    Board<char>* board = new XO_5x5_Board();
    Player<char>** players = ui->setup_players();

    GameManager<char> x_o_game(board, players, ui);
    x_o_game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
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

    delete ui;
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

    delete ui;
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

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_word_TicTacToe(){
    UI<char>* ui = new Word_UI();
    Board<char>* board = new Word_Board();

    Player<char>** players = ui->setup_players();
    
    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Pyramid_TicTacToe(){
    UI<char>* ui = new Pyramid_UI();
    Board<char>* board = new Pyramid_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Diamond_TicTacToe(){
    UI<char>* ui = new Diamond_UI();
    Board<char>* board = new Diamond_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
    delete board;
    for (int i = 0; i < 2; i++){
        delete players[i];
    }
    delete[] players;
}

void play_Obstacles_TicTacToe(){
    UI<char>* ui = new Obstacles_UI();
    Board<char>* board = new Obstacles_Board();

    Player<char>** players = ui->setup_players();

    GameManager<char> game(board, players, ui);
    game.run();

    delete ui;
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
        cout << "| 11    Obstacles Tic-Tac-Toe        |\n";
        cout << "|                                    |\n";
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

        }else if (choice == "11"){
            play_Obstacles_TicTacToe();
            
        }else{
            cout << "Invalid option! Please try again.\n\n";
            continue;
        } 
    }
    
    return 0;
}