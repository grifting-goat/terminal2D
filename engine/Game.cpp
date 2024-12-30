/*
Implimentation file for game class

created by levi morris - 12/30/24
*/

#include "Game.h"

//public methods

Game::Game() {
    //Map map();
    levelScore = 0;
    timeSpent = 0;
    //get map data

    //temp example
    levelHeight = 1000;
    levelWidth = 1000;
    allocateSpace();
}

Game::Game(Map &map) {
    levelScore = 0;
    timeSpent = 0;
    //get map data
}

void Game::incrementScore(int n) {
    levelScore += n;
}

void Game::setScore(int newScore) {
    levelScore = newScore;
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

void Game::update() {
    if (gTick != nullptr) {timeSpent += *gTick;}
}

Game::~Game() {
    deallocateSpace();
}

//private helper functions

void Game::allocateSpace() {
    //makes a char array such that the game space can be indexed space[r][c]
    space = new char*[levelHeight];
    for (int i = 0; i < levelHeight; i++) {space[i] = new char[levelWidth];}

}

void Game::deallocateSpace() {
    //no more game space
    for (int i = 0; i < levelHeight; i++) {delete[] space[i];}
    delete[] space;
}