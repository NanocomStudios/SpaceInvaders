
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

#include "screenCtrl.h"
#include "menu.h"
#include "game.h"

#define PlayerFireRate 200
#define PlayerMoveSpeed 20

using namespace std;

short bottom = 24;
const short shipCount = 14;

bool bulletCollision(short id);



//77 - right
//75 - left
//72 - up
//80 - down

class Bullet {
public:
    short x;
    short y;
    short damage = 1;
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
        if (bulletCollision(id)) {
            state = 1;
        }

        moveCsr(y, x - 1);
        cout << " ";

        if (state == 0) {

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
        return false;
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

struct enemyLayer {
    short direction;
    short speed;
};

enemyLayer eLayers[3] = { {1,1},{-1,2},{1,1} };

class eShip {
public:
    short x = 90;
    short y = 10;
    short health = 1;
    short state = 0;
    short layer;

    clock_t explosionClock = clock();
    clock_t moveClock = clock();
    Bullet bullet;

    void draw(short newX, short newY) {
        moveCsr(newY - 1, newX - 2);
        cout << "\\===/";

        moveCsr(newY, newX - 1);
        cout << "\\X/";

        moveCsr(newY + 1, newX );
        cout << "=";


        x = newX;
        y = newY;
    }

    void destroy() {
        moveCsr(y - 1, x - 2);
        cout << " *** ";

        moveCsr(y, x - 2);
        cout << "*****";

        moveCsr(y + 1, x - 2);
        cout << " *** ";

    }

    void remove() {
        moveCsr(y - 1, x - 2);
        cout << "     ";

        moveCsr(y, x - 2);
        cout << "     ";

        moveCsr(y + 1, x - 2);
        cout << "     ";

    }

    void moveSide() {
        remove();
        draw(x + (eLayers[layer].direction * eLayers[layer].speed), y);
    }

    bool canCollide(short xIn, short yIn) {
        switch (yIn - y) {
        case -1:
            return (((xIn - x) >= -2) && ((xIn - x) <= 3));
            break;
        case 0:
            return (((xIn - x) >= -1) && ((xIn - x) <= 2));
            break;
        case 1:
            return (xIn == x);
            break;
        }
        return false;
    }

    void animate() {
        clock_t currentClock = clock();

        if (health <= 0) {
            if (state == 0) {
                destroy();
                state = 1;
                explosionClock = currentClock;
            }
        }

        if ((currentClock - explosionClock) > 300) {
            
            if (state == 1) {
                remove();
                state = 2;
            }
            
            explosionClock = currentClock;
        }

        if ((currentClock - moveClock) > 200) {

            if (state == 0) {
                moveSide();
            }

            moveClock = currentClock;
        }
    }

};



class eStation {
public:
    short x = 90;
    short y = 10;
    short health = 2;
    short state = 0;

    short layer;

    clock_t explosionClock = clock();

    Bullet bullet;

    void draw(short newX, short newY) {

        moveCsr(newY - 1, newX - 3);
        cout << "/=====\\";

        moveCsr(newY, newX - 3);
        cout << "|X|#|X|";

        moveCsr(newY + 1, newX - 3);
        cout << "\\*/ \\*/";

        x = newX;
        y = newY;
    }

    void destroy() {
        moveCsr(y - 1, x - 3);
        cout << "/** **\\";

        moveCsr(y, x - 3);
        cout << "|*****|";

        moveCsr(y + 1, x - 3);
        cout << "\\** **/";

        moveCsr(y + 2, x - 3);
        cout << " * * * ";
    }

    void remove() {

        moveCsr(y - 1, x - 3);
        cout << "       ";

        moveCsr(y, x - 3);
        cout << "       ";

        moveCsr(y + 1, x - 3);
        cout << "       ";

        moveCsr(y + 2, x - 3);
        cout << "       ";
    }

    void moveSide() {
        remove();
        draw(x + (eLayers[layer].direction * eLayers[layer].speed), y);
    }

    bool canCollide(short xIn, short yIn) {
        switch (yIn - y) {
        case -1:
            return (((xIn - x) >= -2) && ((xIn - x) <= 4));
            break;
        case 0:
            return (((xIn - x) >= -2) && ((xIn - x) <= 4));
            break;
        case 1:
            return (((xIn - x) >= -2) && ((xIn - x) <= 4));
            break;
        case 2:
            return (xIn == x);
            break;
        }
        return false;
    }

    void animate() {
        clock_t currentClock = clock();
        if (health <= 0) {
            if (state == 0) {
                destroy();
                state = 1;
                explosionClock = currentClock;
            }
        }

        if ((currentClock - explosionClock) > 300) {

            if (state == 1) {
                remove();
                state = 2;
            }

            explosionClock = currentClock;
        }

        

    }
};
vector <eShip> eShips;
vector <eStation> eStations;

bool bulletCollision(short id) {
    for (int i = 0; i < eShips.size(); i++) {
        if ((eShips[i].canCollide(bullets[id].x, bullets[id].y)) && (eShips[i].state == 0)) {
            eShips[i].health -= bullets[id].damage;
            return true;
        }
    }
    for (int i = 0; i < eStations.size(); i++) {
        if ((eStations[i].canCollide(bullets[id].x, bullets[id].y)) && (eStations[i].state == 0)) {
            eStations[i].health -= bullets[id].damage;
            return true;
        }
    }
    return false;
}

int inp;
void game()
{
    
    system("cls");
    Player player;

    drawPlayField();
    player.draw(40);

    for (int i = 0; i < 7; i++) {
        eShip e;
        e.draw(10 + (i * 10) , 10);
        e.layer = 0;
        eShips.push_back(e);
    }

    for (int i = 0; i < 7; i++) {
        eShip e;
        e.draw(10 + (i * 10), 15);
        e.layer = 1;
        eShips.push_back(e);
    }

    for (int i = 0; i < 4; i++) {
        eStation e;
        e.draw(17 + (i * 15), 5);
        e.layer = 2;
        eStations.push_back(e);
    }

    int destroyShip = 0;
    int selectedShip = 0;

    clock_t previousClock = clock();
    clock_t currentClock = clock();
    clock_t bulletClock = clock();
    clock_t playerClock = clock();
    clock_t l1moveClock = clock();
    clock_t l2moveClock = clock();
    clock_t l3moveClock = clock();


    while (1) {
        Sleep(1);
        if ((GetKeyState(0x27) == (-128)) || (GetKeyState(0x27) == (-127))) { // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
            if ((clock() - playerClock) > PlayerMoveSpeed) {
                if (player.position < 77) {
                    player.draw(player.position + 1);
                }
                playerClock = clock();
            }
        }
        if ((GetKeyState(0x25) == (-128)) || (GetKeyState(0x25) == (-127))) {

            if ((clock() - playerClock) > PlayerMoveSpeed) {
                if (player.position > 6) {
                    player.draw(player.position - 1);
                }
                playerClock = clock();
            }
        }
        if ((GetKeyState(0x1b) == -127) || (GetKeyState(0x1b) == -128)) {
            eShips.erase(eShips.begin(), eShips.end());
            bullets.erase(bullets.begin(), bullets.end());
            eStations.erase(eStations.begin(), eStations.end());
            system("cls");
            drawMenu();
            return;
        }
        if ((GetKeyState(0x20) == (-128)) || (GetKeyState(0x20) == (-127))) {
            bool okToFire = false;

            if ((clock() - bulletClock) > PlayerFireRate) {
                okToFire = true;
                bulletClock = clock();
            }

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
        
        
        currentClock = clock();
        if ((currentClock - previousClock) > 10) {
            for (int i = 0; i < bullets.size(); i++) {
                if (bullets[i].animate(i)) {
                    bullets.erase(bullets.begin() + i);
                }
                else {
                    for (int j = 0; j < eShips.size(); j++) {
                        if (eShips[j].canCollide(bullets[i].x, bullets[i].y)) {
                            
                            if (eShips[j].state == 2) {
                                eShips.erase(eShips.begin() + j);
                            }
                        }
                    }
                    for (int j = 0; j < eStations.size(); j++) {
                        if (eStations[j].canCollide(bullets[i].x, bullets[i].y)) {

                            if (eStations[j].state == 2) {
                                eStations.erase(eStations.begin() + j);
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < eShips.size(); i++) {
                eShips[i].animate();
            }

            for (int i = 0; i < eStations.size(); i++) {
                eStations[i].animate();
            }

            for (int i = 0; i < bullets.size(); i++) {
                if (bullets[i].state == 1) {
                    bullets.erase(bullets.begin() + i);
                }
            }

            previousClock = currentClock;
        }

        for (int i = 0; i < eShips.size(); i++) {
            if ((eShips[i].x + 4) >= 79) {
                eLayers[eShips[i].layer].direction = -1;
                //eShips[i].moveClock = 0;
            }
            else if ((eShips[i].x - 4) <= 1) {
                eLayers[eShips[i].layer].direction = 1;
                //eShips[i].moveClock = 0;
            }
        }

        
    }
    
    while (1);
}
