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
public:

    Display();

    Display(int fixedWidth, int fixedHeight);

    //test to see if basics is working
    void testDisplay(char c);

    //update the display(flip is not the correct term but it sounds cool)
    void flip();

    //test if the terminal has been resized
    bool checkResized();

    //resize display
    void resize();

    ~Display();

};



#endif //DISPLAY_H