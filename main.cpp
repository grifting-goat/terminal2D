/*
Driver file for testing the functionallity of 2D terminal game components

created by levi morris - 12/29/24
*/

#include<iostream>
#include <chrono>
#include"engine/Display.h"
#include"engine/Game.h"
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

    Display window;
    window.setFPS(dTick);

    Game game;
    game.attachTime(gTick);

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

        window.testDisplay('.');
        
    }

}