#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

short bottom = 24;

void moveCsr(short row, short col) { // https://en.wikipedia.org/wiki/ANSI_escape_code
    char code[] = "e[000;000H";
    code[0] = 27;
    code[2] = 48 + (row / 100);
    code[3] = 48 + ((row % 100) / 10);
    code[4] = 48 + (row % 10);

    code[6] = 48 + (col / 100);
    code[7] = 48 + ((col % 100) / 10);
    code[8] = 48 + (col % 10);

    //printf("%s", code);
    cout << code;
}

void setForColor(int inp) { // inp - https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit
    inp = inp + 30;
    char code[] = "e[30m";
    code[0] = 27;
    code[2] = 48 + (inp / 10);
    code[3] = 48 + (inp % 10);

    printf("%s", code);
}

void drawPlayField() {
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
    cout << endl;
    for (int i = 0; i < 23; i++) {
        cout << "|";
        for (int j = 0; j < 78; j++) {
            cout << " ";
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
}

//77 - right
//75 - left
//72 - up
//80 - down

class Player {
public: short position = 0;

public:
    void moveRight() {

    }

    void draw(int pos) {
        moveCsr(bottom - 2, position - 4);
        cout << "       ";
        moveCsr(bottom - 2, pos - 1);
        cout << "_";

        moveCsr(bottom - 1, position - 4);
        cout << "       ";
        moveCsr(bottom - 1, pos - 3);
        cout << "_/ \\_";

        moveCsr(bottom, position - 4);
        cout << "       ";
        moveCsr(bottom, pos - 4);
        cout << "|__X__|";

        position = pos;
    }

};

int inp;

int main()
{
    Player player;

    drawPlayField();
    player.draw(40);
    
    while (1) {
        inp = _getch();
        if (inp == 77) {

            if (player.position < 77) {
                player.draw(player.position + 1);
            }
        }
        else if (inp == 75) {

            if (player.position > 6) {
                player.draw(player.position - 1);
            }
        }
        
    }
}