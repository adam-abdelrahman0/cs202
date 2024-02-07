#include <iostream>
#include "C4Board.h"


using namespace std;

C4Board::C4Board() {
    num_cols = 7;
}

void C4Board::play() {
    int turn = 0, col = 0;  // initializes turn counter to zero, current column to temp val
    char current_char = ' '; // current char to store character relevant to each turn ('X' for P1, 'O' for P2)

    cout << "This is Connect 4. Here is your board: \n\n" << endl;
    
    display(); // display starter board

    while (true) {
        if (turn % 2 == 0) {
            cout << " ------------" << endl;
            cout << "| Player 1:  |" << endl;
            cout << " ------------" << endl;
            current_char = 'X';
        }
        else {
            cout << " ------------" << endl;
            cout << "| Player 2:  |" << endl;
            cout << " ------------" << endl;
            current_char = 'O';
        }

        cout << "\n Enter column (-1 to quit): ";

        cin >> col;

        if (col == -1) return; // end program if -1 is entered

        while (col < 0 || col > 6 || board[col].isFull() == 1) { // doesn't allow invalid input if column is out of range or full
            cout << "Invalid entry. Try again: ";
            cin >> col;
            if (col == -1) return;
        }

        board[col].addDisc(current_char); // adds disc only if column is valid
        
        display();

        if (check_winner(col)) {
            cout << current_char << " wins!" << endl;
            return;
        }

        turn++;
        
    }
    

}

void C4Board::display() {
    cout << "\n\n";
    for (int i = board[0].getMaxDiscs(); i >= 0; i--) { // displays disc cells bottom to top
        for (int j = 0; j < num_cols; j++) {
            if (i == board[0].getMaxDiscs()) {
                cout << " " << j << "  | ";
            }
            else {
                cout << " " << board[j].getDisc(i) << "  | ";
            }
        }
        cout << endl;
    }
}

bool C4Board::check_winner(int c) { // c is current column
    int disc_position = board[c].getNumDiscs() - 1; // stores current disc position to search around
    int matches = 0; // must get 4 matches in a row to win
    char disc = board[c].getDisc(disc_position); // character to match
    int max_left = 3, max_right = 3; // default will be 3 to check for a horizontal row of 4
    int max_up_left = 3, max_up_right = 3, max_down_left = 3, max_down_right = 3; // for diagonal ranges
    
    // horizontal
    if (c < max_left) max_left = c;
    if (c > num_cols - max_right) max_right = c;

    for (int i = c - max_left; i <= c + max_right; i++) { // iterates window from leftmost possible to rightmost possible
        if (board[i].getDisc(disc_position) == disc) {
            matches++;

            if (matches == 4) return true;
        }
        else {
            matches = 0;
        }
    }

    // vertical
    matches = 0;

    for (int i = 0; i < board[0].getMaxDiscs(); i++) { // same function as above but vertical
        if (board[c].getDisc(i) == disc) {
            matches++;

            if (matches == 4) return true;
        }
        else matches = 0;
    }

    // diagonal backslash (upper left to bottom right)
    matches = 0;
    
    if (5 - disc_position >= 3) { // calculate upper left
        max_up_left = max_left;   // take minimum of max_left and 5 - disc_position to determine how much space is available
    }
    else if (5 - disc_position < max_left) { // read: min(5 - disc_position, max_left)
        max_up_left = 5 - disc_position;
    }

    if (disc_position < max_right) {
        max_down_right = disc_position;
    }
    else max_down_right = max_right;

    int row_track = 0; // tracks current row subtractor to compare values from top to bottom

    for (int i = c - max_up_left; i <= c + max_down_right; i++) { // iterates through window similar to horizontal check
        if (board[i].getDisc(disc_position + max_up_left - row_track) == disc) { // topmost value is at row_track = 0, and goes down as row_track increases
            matches++;
        }
        else matches = 0;

        if (matches == 4) return true;

        row_track++;
    }

    // diagonal forward slash (bottom left to upper right)
    matches = 0;
    row_track = 0;
    
    if (5 - disc_position >= 3) { // calculate upper right
        max_up_right = max_right; // invert processes from previous diagonal check
    }
    else if (5 - disc_position < max_right) {
        max_up_right = 5 - disc_position;
    }

    if (disc_position < max_left) {
        max_down_left = disc_position;
    }
    else max_down_left = max_left;

    for (int i = c - max_down_left; i <= c + max_up_right; i++) {
        if (board[i].getDisc(row_track) == disc) { // since values are compared bottom to top, row_track starts at zero and goes within range of i
            matches++;
        }
        else matches = 0;

        if (matches == 4) return true;

        row_track++;
    }

}


