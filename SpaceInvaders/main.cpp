#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

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
    char code[] = "\e[30m";

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

int x = 50;
int y = 20;
int inp = 0;
//77 - right
//75 - left

int main()
{

    drawPlayField();
    moveCsr(y, x);
    cout << "X";
    
    while (1) {
        inp = _getch();
        if (inp == 77) {
            moveCsr(y, x);
            cout << " ";

            if (x < 79) {
                x++;
                moveCsr(y, x);
                cout << "X";
            }
            else {
                moveCsr(y, x);
                cout << "X";
            }
        }
        else if (inp == 75) {
            moveCsr(y, x);
            cout << " ";

            if (x > 2) {
                x--;
                moveCsr(y, x);
                cout << "X";
            }
            else {
                moveCsr(y, x);
                cout << "X";
            }
        }
        else if (inp == 80) {
            moveCsr(y, x);
            cout << " ";

            if (y < 24) {
                y++;
                moveCsr(y, x);
                cout << "X";
            }
            else {
                moveCsr(y, x);
                cout << "X";
            }
        }
        else if (inp == 72) {
            moveCsr(y, x);
            cout << " ";

            if (y > 2) {
                y--;
                moveCsr(y, x);
                cout << "X";
            }
            else {
                moveCsr(y, x);
                cout << "X";
            }
        }
        
    }
}