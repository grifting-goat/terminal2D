/*
Header File for Display class

handles displaying the graphics and the terminal window

created by levi morris - 12/29/24
*/


#ifndef DISPLAY_H
#define DISPLAY_H

#include<windows.h>
#include<stdexcept>

class Display {

private:
        HANDLE hCmd; //Handle for the console window
        DWORD dwBytesWritten; //windows stuff

        int tWidth; //width of terminal
        int tHeight; //height of terminal
        wchar_t *frame; //frame buffer for the display

        //properties
        bool resizable;
        bool showFramesPerSecond;

        //attached vars
        double *dTick;
        std::pair<float, float> *camera; //<r.c>
public:
    //constructor
    Display();

    //static display window
    Display(int fixedWidth, int fixedHeight);

    //test to see if basics is working
    void testDisplay(char c);

    //attaches the camera
    void attachCamera(std::pair<float, float> &camPos);

    //update the frame buffer
    void update();

    //update the display(flip is not the correct terminology but it sounds cool)
    void flip();

    //test if the terminal has been resized
    bool checkResized();

    //resize display
    void resize();

    //turns on fps and attaches a tick varble
    void setFPS(double &tick);

    //set fps to on or off
    void showFPS(bool show);

    //destructor
    ~Display();

};



#endif //DISPLAY_H