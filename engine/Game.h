/*
header file for game class

created by levi morris - 12/30/24
*/


#ifndef GAME_H
#define GAME_H

#include <queue>
#include <string>
#include "Map.h"

class Game {

private:
    std::queue<std::string> gameMessages;
    std::queue<std::string> gameAnnouncments;

    int levelScore; //arbitrary units
    double timeSpent; //seconds

    int levelWidth;
    int levelHeight;

    double *gTick = nullptr; //get timing data

    Map *levelMap; //get map
    char** space;

public:
    //start a new game
    Game();

    //new game with map
    Game(Map &map);

    //i wonder what this does
    void incrementScore(int n);

    //let me guess
    void setScore(int newScore);

    //grab the time variable
    void attachTime(double& tick);

    //add a message to the queue
    void pushMessage(std::string message);

    //display the front message
    std::string popMessage();

    //add an announcement to the queue
    void pushAnnouncement(std::string announcement);

    //display the front announcement
    std::string popAnnouncement();

    //run once every game cycle;
    void update();

    ~Game();

private:
    //build the char array for the game space
    void allocateSpace();

    //unbuild the char array for the game space
    void deallocateSpace();

};


#endif //GAME_H