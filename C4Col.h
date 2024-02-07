#include <iostream>

class C4Col {

    public:
        C4Col(); // default constructor
        int isFull(); 
        int getMaxDiscs();
        int getNumDiscs();
        char getDisc(int);
        void addDisc(char);


    private:
        int cur_discs;
        int max_discs; // same as number of rows (6)
        char discs[6]; // char array that holds discs for each row

};
