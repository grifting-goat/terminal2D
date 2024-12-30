/*
Implimentation file for display class

created by levi morris - 12/29/24
*/

#include "Display.h"
#include <string>

Display::Display() {
        // Create Frame // Get Windows dimensions  // goofy windows stuff
        hCmd = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hCmd);
        if (hCmd == INVALID_HANDLE_VALUE) {throw std::runtime_error("Failed to create console screen buffer");}
        dwBytesWritten = 0;

        CONSOLE_SCREEN_BUFFER_INFO csbi; //get information about the console
        if (!GetConsoleScreenBufferInfo(hCmd, &csbi)) {
            CloseHandle(hCmd);
            throw std::runtime_error("Failed to get console screen buffer info");
        }

        tWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        tHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        frame = new wchar_t[tWidth * tHeight];

        resizable = true;
}

Display::Display(int fixedWidth, int fixedHeight) {
        // Create Frame // goofy windows stuff
        hCmd = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(hCmd);
        if (hCmd == INVALID_HANDLE_VALUE) {throw std::runtime_error("Failed to create console screen buffer");}
        dwBytesWritten = 0;

        tWidth = fixedWidth;
        tHeight = fixedHeight;
        frame = new wchar_t[tWidth * tHeight];

        resizable = false;
}

void Display::testDisplay(char c) {
    if (this->checkResized()) {this->resize();}//test for resize

    for (int i = 0; i < tWidth * tHeight-1; i++) {frame[i] = c;} //make it all the character

    this->flip(); //update display
}

void Display::attachCamera(std::pair<float, float> &camPos) {
    camera = &camPos;
}

void Display::update() {
    //get data from Game
    //use the attached camera to add the relevant stuff to display buffer(frame)
}

void Display::flip() {
    //add postProcess overlays
    if(showFramesPerSecond) {
        std::wstring fps = L"FPS: " + std::to_wstring(static_cast<int>(1/(*dTick)));
        if (fps.size() < tWidth) { //dont try to wrie at frame[-1]
            for (int i = 0; i < fps.size(); i++) {frame[tWidth-fps.size()+i] = fps[i];}
        }
    }

    //displays the content of the frame
    frame[tWidth * tHeight - 1] = L'\0';
    WriteConsoleOutputCharacterW(hCmd, frame, tWidth * tHeight, {0, 0}, &dwBytesWritten);



}

bool Display::checkResized() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; //console window
    GetConsoleScreenBufferInfo(hCmd, &csbi); //get information about the console

    int testWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int testHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    //if a change has occured
    if (testWidth != tWidth || testHeight != tHeight) {return true;}

    return false;
}

void Display::resize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; //console window
    //get information about the console
    if (!GetConsoleScreenBufferInfo(hCmd, &csbi)) {
        CloseHandle(hCmd);
        throw std::runtime_error("Failed to get console screen buffer info");
    }

    delete[] frame;
    //update the height, width and frame
    tWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    tHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    frame = new wchar_t[tWidth * tHeight];

}

void Display::setFPS(double &tick) {
    showFramesPerSecond = true;
    dTick = &tick;  
}

void Display::showFPS(bool show) {
    showFramesPerSecond = show;
}

Display::~Display() {
    CloseHandle(hCmd);
    delete[] frame;
}