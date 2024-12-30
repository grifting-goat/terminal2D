/*
Header File for Display class

handles displaying the graphics and the terminal window

created by levi morris - 12/29/24
*/


#ifndef DISPLAY_H
#define DISPLAY_H

#include <windows.h>
#include <stdexcept>
#include "Game.h"
#include "Display.h"
#include <string>
#include <iostream>

class Display {

private:
        HANDLE hCmd; //Handle for the console window
        DWORD dwBytesWritten; //windows stuff

        int tHeight; //height of terminal
        int tWidth; //width of terminal

        char centerChar = '@';
        char voidChar = '.';
        //hurts preformance but improves the game speed
        char voidArr[12] = {'.', '.', '.','.','.','.','.','.','.', '-','~', '|'};

        


        wchar_t *frame; //frame buffer for the display

        //properties
        bool resizable;
        bool showFramesPerSecond;
        bool showCameraCenter;
        bool dynamicVoid;

        //attached read only vars
        const double *dTick = nullptr;
        const std::pair<float, float> *camera = nullptr; //<r.c>
        const Game *game = nullptr;
        const int *gHeight;
        const int *gWidth;
        const char** gameSpace;
public:
    //constructor
    Display();

    //static display window
    Display(int fixedWidth, int fixedHeight);

    //attach game
    bool attachGame(Game &agame);

    //attaches the camera
    bool attachCamera(std::pair<float, float> &camPos);

    //turns on fps and attaches a tick varble
    bool attachTick(double &tick);

    //update the frame buffer
    void update();

    //update the display(flip is not the correct terminology but it sounds cool)
    void flip();

    //test if the terminal has been resized
    bool checkResized();

    //resize display
    void resize();

    //set fps to on or off
    void toggleFramesPerSecond(bool show);

    //i wonder
    void toggleCameraCenter(bool show);

    void toggleDynamicVoid(bool show);

    //destructor
    ~Display();

private: //helper functions

    bool inBounds(int r, int c);
};



#endif //DISPLAY_H