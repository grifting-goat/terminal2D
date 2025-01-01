/*
Implimentation file for inherited Player class

created by levi morris - 12/30/24
*/

#include "Player.h"

template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
    return std::pair<T1, T2>(p1.first + p2.first, p1.second + p2.second);
}

template <typename T1, typename T2>
std::pair<T1, T2> operator-(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
    return std::pair<T1, T2>(p1.first - p2.first, p1.second - p2.second);
}

Player::Player() {
    setMass(defaultMass);
    setHealth(defaultHealth);
    setForce(defaultForce);
    setHitBox(playerHitbox);
    setRules(true,true,false,false);
}

void Player::attachDisplay(Display &newDisp) {
    screen = &newDisp;
    dTick = screen->getTick();
}

void Player::attachSpace(const char** gSpace, const int* row, const int* col) {
    gameSpace = gSpace;
    spaceR = row;
    spaceC = col;
}


void Player::getInputs() {

        lastInput.clear();

        //shift //modifier so must come first
        if      (GetAsyncKeyState(VK_SHIFT) & 0x8000) {lastInput.push_back('^');}

        //up/down
        if      (GetAsyncKeyState('W') & 0x8000) {lastInput.push_back('w');}
        else if (GetAsyncKeyState('S') & 0x8000) {lastInput.push_back('s');;}

        //side/side
        if      (GetAsyncKeyState('D') & 0x8000) {lastInput.push_back('d');}
        else if (GetAsyncKeyState('A') & 0x8000) {lastInput.push_back('a');}

        //space
        if      (GetAsyncKeyState(VK_SPACE) & 0x8000) {lastInput.push_back(' ');}

        
}

void Player::simplePhys() {

    setForce(defaultForce);
    setMomentum({0,0});


    for (auto input : lastInput) {
        switch (input) {
            case 'w':
                setMomentumRow(-getForce()/getMass());
                break;
            case 's':
                setMomentumRow(getForce()/getMass());
                break;
            case 'd':
                setMomentumCol(getForce()/getMass());
                break;
            case 'a':
                setMomentumCol(-getForce()/getMass());
                break;
            case '^':
                setForce(defaultForce*1.8f);
                break;     
        }
    }

    //simpleColision();

}

void Player::update() {
    incrementPosition({getMomentum().first * (*dTick) , getMomentum().second * (*dTick)});
}


//private helper funcitons

void Player::simpleColision() {
    char solid = '#'; //what can collide with

    std::pair<float, float> pos = getPosition();
    for (auto offset : getHitBox()) { //for each part of the hitbox
        std::pair<float, float> test = pos + static_cast<std::pair<float,float>>(offset);
        
        //if bad
        if (check(test, solid)) {
            //for rows
            setMomentumRow(-getMomentum().first); //flip
            test = test + std::make_pair(getMomentum().first * static_cast<float>(*dTick), 0.0f); //unupdate

            //if still bad
            if (check(test, solid)) {
                test = test - std::make_pair(getMomentum().first * static_cast<float>(*dTick), 0.0f); //unupdate //unupdate
                setMomentumRow(-getMomentum().first); //unflip
                
            }
            else { //if good
                test = test - std::make_pair(getMomentum().first * static_cast<float>(*dTick), 0.0f); //unupdate //unupdate
                return;
            }

            //for cols
            setMomentumCol(-getMomentum().second); //flip
            test = test + std::make_pair(0.0f, getMomentum().second * static_cast<float>(*dTick)); //update

            //if still bad
            if (check(test, solid)) {
                test = test - std::make_pair(0.0f, getMomentum().second * static_cast<float>(*dTick)); //unupdate
                setMomentumCol(-getMomentum().second); //unflip
                
            }
            else { //if good
                test = test - std::make_pair(0.0f, getMomentum().second * static_cast<float>(*dTick)); //unupdate
                
            }
        }

    }

}

bool Player::check(std::pair<float, float> test, char bad) {
    if (static_cast<int>(test.first) >= 0 && static_cast<int>(test.first) < (*spaceR)
    && static_cast<int>(test.second) >= 0 && static_cast<int>(test.second) < (*spaceC)) {
        if (gameSpace[static_cast<int>(test.first)][static_cast<int>(test.second)] == bad) {return true;}
        else {return false;}
    }
    return true;
}

Player::~Player() {

    delete screen;
    delete dTick;
}