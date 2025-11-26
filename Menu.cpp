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
using namespace std;

void playNumerical(){
    
}

int main(){
    string choice;
    while(true){
        cout << "For exit Enter 0\n";
        cout << "For Numerical Tic-Tac-Toe Enter 1\n";
        cout << "For Misere Tic-Tac-Toe Enter 2\n";
        cout << "For Four-in-a-row Enter 3\n";
        cout << "For 5x5 Tic-Tac-Toe Enter 4\n";
        cout << "For Infinity Tic-Tac-Toe Enter 5\n";
        cout << "For 4x4 Tic-Tac-Toe Enter 6\n";
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

        }else if (choice == "2"){
            srand(time(0));

            Misere_UI* ui = new Misere_UI();
            Misere_Board* board = new Misere_Board();

            Player<char>** players = new Player<char>*[2];
            string name1, name2;
            string type_choice;

            cout << "Enter Player 1 name: ";
            cin >> name1;
            cout << "1: Human, 2: Computer: ";
            cin >> type_choice;
            players[0] = ui->create_player(name1, 'X', type_choice == "1" ? PlayerType::HUMAN : PlayerType::COMPUTER);

            cout << "Enter Player 2 name: ";
            cin >> name2;
            cout << "1: Human, 2: Computer: ";
            cin >> type_choice;
            players[1] = ui->create_player(name2, 'O', type_choice == "1" ? PlayerType::HUMAN : PlayerType::COMPUTER);

            players[0]->set_board_ptr(board);
            players[1]->set_board_ptr(board);

            GameManager<char> game(board, players, ui);
            game.run();

            delete players[0];
            delete players[1];
            delete[] players;
            delete board;
            delete ui;
        }else if(choice == "3"){
            srand(static_cast<unsigned int>(time(0)));  
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

        }else if(choice == "4"){
            srand(static_cast<unsigned int>(time(0)));

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
        }else if (choice == "5"){
            Infinity_UI ui;
            Player<char>** players = ui.setup_players();
            Infinity_Board board;
            GameManager<char> game(&board, players, &ui);
            game.run();
            delete players[0]; delete players[1]; delete[] players;

        } else if (choice == "6"){
            FourByFour_UI ui;
            string n1, n2;
            int t1, t2;
            cout << "Enter player 1 name: "; cin >> n1;
            cout << "Choose type (1=Human,2=Computer): "; cin >> t1;
            cout << "Enter player 2 name: "; cin >> n2;
            cout << "Choose type (1=Human,2=Computer): "; cin >> t2;

            Player<char>* p1 = new Player<char>(n1, 'X', t1 == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);
            Player<char>* p2 = new Player<char>(n2, 'O', t2 == 1 ? PlayerType::HUMAN : PlayerType::COMPUTER);

            FourByFour_Board board;
            Player<char>** arr = new Player<char>*[2] {p1, p2};
            GameManager<char> game(&board, arr, &ui);
            game.run();
            delete p1; delete p2; delete[] arr;

        }else{
            cout << "Invalid choice! Please try again.\n";
            continue;
        } 
    }
    
    return 0;
}