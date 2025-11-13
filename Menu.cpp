#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "Numerical.h"
using namespace std;

int main(){
    string choice;
    while(true){
        cout << "For exit Enter 0\n";
        cout << "For Numerical Tic-Tac-Toe Enter 1\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "0"){
            break;
        }else if (choice == "1"){
            srand(time(0));

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

        }else{
            cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}