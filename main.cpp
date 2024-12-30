/*
Driver file for testing the functionallity of 2D terminal game components

created by levi morris - 12/29/24
*/

#pragma comment(lib, "User32.lib")

#include <iostream>
#include <Windows.h>
#include <chrono>
#include "engine/Display.h"
#include "engine/Game.h"
using namespace std;

const int TICK_RATE = 120;
const double TICK_TIME = 1/TICK_RATE;


int main() {
    //handle timing
    auto startTime = chrono::system_clock::now();

    //handle display tick
    auto disp1 = chrono::system_clock::now();
    auto disp2 = chrono::system_clock::now();

    //handle game tick
    auto tick1 = chrono::system_clock::now();
    auto tick2 = chrono::system_clock::now();

    double dTick; //display tick
    double gTick; //game tick

    std::pair<float, float> clientPos = {250, 250}; //temp for stuff
    float speed = 15; //also temp

    Game game;
    game.attachTime(gTick);
    game.voidSpace(' ');

    Display window;
    //attach relavent obj/data
    window.attachGame(game);
    window.attachCamera(clientPos);
    window.attachTick(dTick);
    //toggle settings
    window.toggleFramesPerSecond(true);
    window.toggleCameraCenter(true);
    window.toggleDynamicVoid(true);    

    while(true) {
        //timing
        disp2 = chrono::system_clock::now();
        tick2 = disp2;

        //display tick
        chrono::duration<double> elapsedTime = disp2 - disp1;
        dTick = elapsedTime.count();
        disp1 = disp2;

        //game tick
        elapsedTime = tick2 - tick1;
        gTick = elapsedTime.count();

        //keeps the game tick rate relatively constant
        if (gTick >= TICK_TIME) {
            game.update();
            tick1 = tick2;
        }

        //temp this will later be handeled in player class

        //check for exit
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {exit(0);}
        if (GetAsyncKeyState(VK_BACK) & 0x8000) {exit(0);}

        //row travesal
        if      (GetAsyncKeyState('W') & 0x8000) {clientPos.first -= speed*dTick;}
        else if (GetAsyncKeyState('S') & 0x8000) {clientPos.first += speed*dTick;}

        //col traversal
        if      (GetAsyncKeyState('D') & 0x8000) {clientPos.second += speed*dTick;}
        else if (GetAsyncKeyState('A') & 0x8000) {clientPos.second -= speed*dTick;}

///*
        
        window.update();
        window.flip();
      
//*/

}

}