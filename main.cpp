/*
Driver file for testing the functionallity of 2D terminal game components

created by levi morris - 12/29/24
*/

#include<iostream>
#include"engine/Display.h"
using namespace std;

int main() {
    Display window;

    while(true) {
        window.testDisplay(50 + rand()%50);
        Sleep(500);
    }

}