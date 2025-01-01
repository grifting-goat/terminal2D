/*
Implimentation file for display class

created by levi morris - 12/29/24
*/

//known issues
//- resize does not always work perfectly

#include "Display.h"


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
        showFramesPerSecond = false;
        showCameraCenter = false;
        dynamicVoid = false;
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
        showFramesPerSecond = false;
        showCameraCenter = false;
        dynamicVoid = false;
}


bool Display::attachGame(Game &agame) {
    if (&agame != nullptr) {
        //get the game object and gamespace
        game = &agame;
        gameSpace = game->getSpaceRef();

        //get dimensions easier
        auto dims = game->getSpaceDimRefs();
        gHeight = dims.first;
        gWidth = dims.second;

        return true;
    }
    return false;//attachment failed
}

bool Display::attachCamera(std::pair<float, float> &camPos) {
    if (&camPos != nullptr) {camera = &camPos; return true;}
    return false;//attachment failed
}

bool Display::attachCamera(std::pair<float, float> *camPos) {
    if (camPos != nullptr) {camera = camPos; return true;}
    return false;//attachment failed
}

bool Display::attachTick(double &tick) {
    dTick = &tick;  //add protections later
    return true;
}

void Display::update() {
    if (this->checkResized() && resizable) {this->resize();}//test for resize

    int leftBound = static_cast<int>(camera->second +.5f) - (tWidth/2);
    int rightBound = static_cast<int>(camera->second +.5f) + (tWidth/2);
    int lowerBound = static_cast<int>(camera->first +.5f) - (tHeight/2);
    int upperBound = static_cast<int>(camera->first +.5f) + (tHeight/2);

    int n = 0;
    for (int r = lowerBound; r < upperBound; r++) {
        for (int c = leftBound; c < rightBound; c++) {
            //if is inbounds //do not flip order
            if (inBounds(r,c) && gameSpace[r][c] != 'b') {
                frame[n++] = gameSpace[r][c];
            }
            else{
                if(dynamicVoid) {frame[n++] = voidArr[rand()%(sizeof(voidArr))];}
                else {frame[n++] = voidChar;}
            }

            if (n >= tWidth * tHeight) {break;}

        }
    }

}

void Display::flip() {
    //add postProcess overlays
    if(showFramesPerSecond) {
        std::wstring fps = L"FPS: " + std::to_wstring(static_cast<int>(1/(*dTick)));
        if (fps.size() < tWidth) { //dont try to wrie at frame[-1]
            for (int i = 0; i < fps.size(); i++) {frame[tWidth-fps.size()+i] = fps[i];}
        }
    }
    if(showCameraCenter) {frame[tWidth * (tHeight/2) + (tWidth/2)] = centerChar;}

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

void Display::toggleFramesPerSecond(bool show) {
    showFramesPerSecond = show;
}

void Display::toggleCameraCenter(bool show) {
    showCameraCenter = show;
}

void Display::toggleDynamicVoid(bool show) {
    dynamicVoid = show;
}

const double* Display::getTick() {
    if (dTick != nullptr) {return dTick;}
    else {throw std::runtime_error("requested tick from unattached display"); return dTick;}
}

Display::~Display() {
    CloseHandle(hCmd);
    delete[] frame;
}

//helper private funcitons

bool Display::inBounds(int r, int c) {
    if (r >= 0 && r < *gHeight && c >= 0 && c < *gWidth) {return true;}
    return false;
}