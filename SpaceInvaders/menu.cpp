#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <vector>

#include "menu.h"
#include "screenCtrl.h"
#include "game.h"

using namespace std;

short menuSelection = 0;
vector <thread> song;
int main() {
    
    setCursor(false);
    system("cls");
    
    drawMenu();

    drawStartGame();
    drawControlles();
    drawExit();

    int inp;

    while (1) {
        inp = _getch();

        if (inp == 72) {
            if (menuSelection > 0) {
                menuSelection--;
            }
        }
        else if (inp == 80) {
            if (menuSelection < 2) {
                menuSelection++;
            }
        }
        else if ((inp == 13) || (inp == 32)) {
            if (menuSelection == 0) {
                game();
            }
            else if (menuSelection >= 2) {
                normalColor();
                system("cls");
                return 0;
            }
        }

        drawStartGame();
        drawControlles();
        drawExit();

    }

}

void drawMenu() {
    drawPlayField();

    moveCsr(2, 5);
    cout << "/===   |====\\      /=\\      /====  /====";
    moveCsr(3, 5);
    cout << "|      |    |     /   \\     |      |";
    moveCsr(4, 5);
    cout << "\\===\\  |====/    /=====\\    |      |===";
    moveCsr(5, 5);
    cout << "    |  |        /       \\   |      |";
    moveCsr(6, 5);
    cout << " ===/  |       /         \\  \\====  \\====";

    moveCsr(7, 20);
    cout << "===== |\\   | \\      /    /=\\     |===\\  |===  |==\\  /===";
    moveCsr(8, 20);
    cout << "  |   | \\  |  \\    /    /   \\    |   |  |__   |==/  \\___";
    moveCsr(9, 20);
    cout << "  |   |  \\ |   \\  /    /=====\\   |   |  |     | \\       \\";
    moveCsr(10, 20);
    cout << "===== |   \\|    \\/    /       \\  |===/  |===  |  \\   ===/";
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

void normalColor() {
    consoleColorSet(40);
    consoleColorSet(37);
}

void invertColor() {
    consoleColorSet(47);
    consoleColorSet(30);
}

void drawStartGame() {
    if (menuSelection == 0) {
        invertColor();
    }
    else {
        normalColor();
    }
    moveCsr(14, 32);
    cout << "   Start Game   ";
}

void drawControlles() {
    if (menuSelection == 1) {
        invertColor();
    }
    else {
        normalColor();
    }
    moveCsr(17, 32);
    cout << "   Controlles   ";
}

void drawExit() {
    if (menuSelection >= 2) {
        invertColor();
    }
    else {
        normalColor();
    }
    moveCsr(20, 32);
    cout << "      Exit      ";
}