#include <iostream>
#include "C4Col.h"

class C4Board {

  public:
    C4Board(); // default constructor
    void display(); // displays board
    void play(); // plays game

  private:
    int num_cols;
    C4Col board[7]; // array of Columns
    bool check_winner(int);

};
