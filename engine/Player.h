/*
header file for player class

created by levi morris - 12/30/24
*/
#ifndef PLAYER_H
#define PLAYER_H

//#pragma comment(lib, "User32.lib")

#include "Entity.h"
#include "Display.h"

#include <Windows.h>

class Display;




class Player : public Entity  {
private:
    std::vector<char> lastInput;

    const float defaultMass = 100;
    const float defaultHealth = 100;
    const float defaultForce = 1500;

    HITBOX playerHitbox = {std::make_pair(0,0)};

    const double *dTick = nullptr; //get timing data

    void movementFucntion();

    void simpleColision(); //will be replaced by physics engine

    bool check(std::pair<float, float> test, char bad);

    Display* screen = nullptr;

    const char** gameSpace = nullptr;

    const int* spaceR = nullptr;
    const int* spaceC = nullptr;

public:

    Player();

    void attachDisplay(Display &newDisp);

    void attachSpace(const char** gSpace, const int* row, const int* col);

    void getInputs();

    void simplePhys(); //will be replaced by physics engine

    void update();

    ~Player();
};

#endif //PLAYER_H