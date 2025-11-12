#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
using namespace std;

int main(){
    string choice;
    while(true){
        bool playing = false;
        cout << "For Numerical Tic-Tac-Toe Enter 1\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "1"){
            //Numerical Tic-Tac-Toe variables and calls here

            playing = true;
        }else{
            cout << "Invalid Choice, Please select a valid number";
        }
        
        //Replaying the games menu
        if (playing){
            string again;
            cout << "If you want to play again Enter 1\nIf you want to close the app Enter anything\n";
            cout << "Enter your choice: ";
            cin >> again;
            if(again != "1"){
                break;
            }
        }
    }
    
    return 0;
}