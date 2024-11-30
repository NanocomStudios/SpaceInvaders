#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "menu.h"
#include "screenCtrl.h"

using namespace std;

void mainMenu() {
	system("cls");

    drawPlayField();

    moveCsr(2,5);
    cout << "/===   |====\\      /=\\      /====  /====";
    moveCsr(3, 5);
    cout << "|      |    |     /   \\     |      |" ;
    moveCsr(4, 5);
    cout << "\\===\\  |====/    /=====\\    |      |===";
    moveCsr(5, 5);
    cout << "    |  |        /       \\   |      |";
    moveCsr(6, 5);
    cout << " ===/  |       /         \\  \\====  \\====";

    moveCsr(7, 20);
    cout << "===== |\\   | \\       /    /=\\     |===\\  |===  |==\\  /===";
    moveCsr(8, 20);
    cout << "  |   | \\  |  \\     /    /   \\    |   |  |__   |==/  \\___";
    moveCsr(9, 20);
    cout << "  |   |  \\ |   \\   /    /=====\\   |   |  |     | \\       \\";
    moveCsr(10, 20);
    cout << "===== |   \\|    \\=/    /       \\  |===/  |===  |  \\   ===/";

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