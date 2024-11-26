#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

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

class eShip {
public:
    short x = 10;
    short y = 90;

    short state = 0;

    void draw(short newX, short newY) {
        moveCsr(x - 1, y - 3);
        cout << "       ";
        moveCsr(newX - 1 , newY - 3);
        cout << "\\=====/";

        moveCsr(x , y - 3);
        cout << "       ";
        moveCsr(newX , newY - 2);
        cout << "\\ X /";

        moveCsr(x +1, y - 3);
        cout << "       ";
        moveCsr(newX +1, newY - 1);
        cout << "\\ /";

        moveCsr(x +2, y - 3);
        cout << "       ";
        moveCsr(newX +2, newY);
        cout << ".";

        x = newX;
        y = newY;
    }

    void destroy() {
        moveCsr(x - 1, y - 3);
        cout << "\\88888/";

        moveCsr(x, y - 3);
        cout << "8\\888/8";

        moveCsr(x + 1, y - 3);
        cout << "88\\X/88";

        moveCsr(x + 2, y - 3);
        cout << " 8 8 8 ";
        state = 1;
    }

    void remove() {
        moveCsr(x - 1, y - 3);
        cout << "       ";

        moveCsr(x, y - 3);
        cout << "       ";

        moveCsr(x + 1, y - 3);
        cout << "       ";

        moveCsr(x + 2, y - 3);
        cout << "       ";
        state = 2;
    }

};

int inp;
clock_t previousClock;
clock_t currentClock;
int main()
{
    Player player;
    eShip eShips[7];

    drawPlayField();
    player.draw(40);

    for (int i = 0; i < 7; i++) {
        eShips[i].draw(10, 10 + (i * 10));
    }

    int destroyShip = 0;
    int selectedShip = 0;

    previousClock = clock();

    while (1) {
        if (_kbhit()) {
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
            else if (inp == 32) {
                short count = 0;
                while (1) {
                    selectedShip = rand() % 7;
                    if (eShips[selectedShip].state == 0) {
                        break;
                    }
                }
                destroyShip = 1;

            }
        }

        currentClock = clock();

        if ((currentClock - previousClock) > 300) {
            if (destroyShip == 1) {
                
                if (eShips[selectedShip].state == 0) {
                    eShips[selectedShip].destroy();
                }
                else {
                    for (int i = 0; i < 7; i++) {
                        if (eShips[i].state == 1) {
                            eShips[i].remove();
                        }
                    }
                }
            }
            previousClock = currentClock;
        }

    }
}