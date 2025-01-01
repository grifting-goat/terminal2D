/*
Implimentation file for game class

created by levi morris - 12/30/24
*/

#include "Game.h"

//public methods

Game::Game() {
    //Map map();
    totalScore = 0;
    timeSpent = 0;
    
    //get map data
    //spaceHeight = map.getDimensions().first;
    //spaceWidth = map.getDimensions().second;
    //allocateSpace();
    //propogateMap(map);
}

Game::Game(Map &map) {
    totalScore = 0;
    timeSpent = 0;

    //get map data
    spaceHeight = map.getDimensions().first;
    spaceWidth = map.getDimensions().second;

    spaceMap = &map;

    allocateSpace();
    propogateMap(map);
    spawns = map.getSpawns();
}

void Game::incrementScore(int n) {
    totalScore += n;
}

void Game::setScore(int newScore) {
    totalScore = newScore;
}

void Game::attachTime(double& tick) {
    gTick = &tick;
}


void Game::pushMessage(std::string message) {
    gameMessages.push(message);
}

std::string Game::popMessage() {
    std::string message;
    if (!gameMessages.empty()) {
        message = gameMessages.front(); gameMessages.pop();
        return message;
    }
    return "";
}

void Game::pushAnnouncement(std::string announcement) {
    gameAnnouncments.push(announcement);
}

std::string Game::popAnnouncement() {
    std::string announcment;
    if (!gameAnnouncments.empty()) {
        announcment = gameAnnouncments.front(); gameAnnouncments.pop();
        return announcment;
    }
    return "";
}

void Game::voidSpace(char c) {
    for (int row = 0; row < spaceHeight; row++) {
        for (int col = 0; col < spaceWidth; col++) {
            space[row][col] = c;
        }
    }
}

std::pair<const int*, const int*> Game::getSpaceDimRefs() const {
    return std::make_pair(&spaceHeight, &spaceWidth);
}

const char** Game::getSpaceRef() const { 
    return const_cast<const char**>(space); 
}

std::vector<std::pair<int,int>> Game::getSpawns() {
    return spawns;
}

void Game::update() {
    if (gTick != nullptr) {timeSpent += *gTick;}
    //update things
}

Game::~Game() {
    deallocateSpace();
}

//private helper functions

void Game::allocateSpace() {
    //makes a char array such that the game space can be indexed space[r][c]
    space = new char*[spaceHeight];
    for (int i = 0; i < spaceHeight; i++) {space[i] = new char[spaceWidth];}

}

void Game::deallocateSpace() {
    //no more game space
    for (int i = 0; i < spaceHeight; i++) {delete[] space[i];}
    delete[] space;
}

void Game::propogateMap(Map &map) {

    space = map.getMap();

}
