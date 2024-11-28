
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

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

class Bullet {
public:
    short x;
    short y;
    
    short state = 0;
    clock_t previousClock;

    void draw(short xIn, short yIn) {
        x = xIn;
        y = yIn;

        moveCsr(y,x - 1);
        cout << "*";

        previousClock = clock();
    }
    bool animate(int id) {
        if (state == 0) {
            moveCsr(y, x - 1);
            cout << " ";

            moveCsr(y - 1, x - 1);
            cout << "*";
            y = y - 1;

            if (y == 2) {
                moveCsr(y, x - 1);
                cout << " ";
                state = 1;
                return true;
            }
            else {
                return false;
            }
        }
    }

};

vector <Bullet> bullets;

class Player {
public: 
    short position = 0;
    

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
    short health = 1;
    short state = 0;

    Bullet bullet;

    void draw(short newX, short newY) {
        moveCsr(x - 1, y - 3);
        cout << "       ";
        moveCsr(newX - 1, newY - 3);
        cout << "\\=====/";

        moveCsr(x, y - 3);
        cout << "       ";
        moveCsr(newX, newY - 2);
        cout << "\\ X /";

        moveCsr(x + 1, y - 3);
        cout << "       ";
        moveCsr(newX + 1, newY - 1);
        cout << "\\ /";

        moveCsr(x + 2, y - 3);
        cout << "       ";
        moveCsr(newX + 2, newY);
        cout << ".";

        x = newX;
        y = newY;
    }

    void destroy() {
        moveCsr(x - 1, y - 3);
        cout << "\\*****/";

        moveCsr(x, y - 3);
        cout << "*\\***/*";

        moveCsr(x + 1, y - 3);
        cout << "**\\X/**";

        moveCsr(x + 2, y - 3);
        cout << " * * * ";
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
int main()
{
    
    system("cls");
	Player player;
    eShip eShips[7];

    drawPlayField();
    player.draw(40);

    for (int i = 0; i < 7; i++) {
        eShips[i].draw(10, 10 + (i * 10));
    }

    int destroyShip = 0;
    int selectedShip = 0;

    clock_t previousClock = clock();
    clock_t currentClock = clock();

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
                bool okToFire = true;
                for (Bullet b : bullets) {
                    if ((b.x == player.position) && (b.y == (bottom - 3))) {
                        okToFire = false;
                    }
                }

                if (okToFire) {
                    Bullet b;
                    b.draw(player.position, bottom - 3);
                    bullets.push_back(b);
                }

            }

        }

        currentClock = clock();
        if ((currentClock - previousClock) > 10) {
            for (int i = 0; i < bullets.size(); i++) {
                if (bullets[i].animate(i)) {
                    bullets.erase(bullets.begin() + i);
                }
            }
            previousClock = currentClock;
        }
    }
}
