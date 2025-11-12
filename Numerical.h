#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <vector>

class Numerical_Board : public Board<char>{

};

class Numerical_Move : public Move<char>{

};

class Numerical_Player : public Player<char>{

};

class Numerical_UI : public UI<char>{

};