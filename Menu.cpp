#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "Numerical.h"
#include "Numerical.cpp"
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
            //Numerical Tic-Tac-Toe variables and calls here

        }else{
            cout << "Invalid Choice, Please select a valid number";
        }
    }
    
    return 0;
}