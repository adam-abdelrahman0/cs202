#include "C4Col.h"

C4Col::C4Col() {
    max_discs = 6;
    cur_discs = 0;
    for (int i = 0; i < max_discs; i++) discs[i] = ' '; // initialize discs with space character
}

int C4Col::isFull() {
    if (cur_discs == max_discs) return 1; // since return type is int, treat 1 as true, meaning full
    
    return 0; // 0 if not full
}
int C4Col::getMaxDiscs() { // returns max discs (i.e. number of rows)
    return max_discs;
}

int C4Col::getNumDiscs() { // returns number of discs currently occupied (index of most significant disc is num_disc - 1)
    return cur_discs;
}

char C4Col::getDisc(int index) { // input testing handled in C4Board.cpp 'play()'
    return discs[index];
}

void C4Col::addDisc(char c) { // input testing handled in C4Board.cpp 'play()'
    discs[cur_discs++] = c;
}