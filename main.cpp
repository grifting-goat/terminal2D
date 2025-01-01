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
#include "engine/Player.h"
#include "engine/Map.h"

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

    Player player;

    Map testMap("rectVoid.txt");

    Game game(testMap);
    game.attachTime(gTick);
    std::pair<int,int> testSpawn = game.getSpawns()[0];
    //game.voidSpace(' ');

    Display window;
    //attach relavent obj/data
    window.attachGame(game);
    window.attachCamera(player.getPositionRefs());
    window.attachTick(dTick);
    //toggle settings
    window.toggleFramesPerSecond(true);
    window.toggleCameraCenter(true);
    window.toggleDynamicVoid(true);   

    player.attachDisplay(window);
    player.setPosition(testSpawn);
    player.attachSpace(game.getSpaceRef(), game.getSpaceDimRefs().first, game.getSpaceDimRefs().first );

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
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {break;}
        if (GetAsyncKeyState(VK_BACK) & 0x8000) {break;}

        player.getInputs();
        player.simplePhys();
        player.update();

        
///*
        
        window.update();
        window.flip();
      
//*/
    }

    return 0;

}