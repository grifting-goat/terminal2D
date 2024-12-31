/*
header file for game class

created by levi morris - 12/30/24
*/


#ifndef GAME_H
#define GAME_H

#include <queue>
#include <string>
#include <vector>

#include "Map.h"
#include "Player.h"

class Game {

private:
    std::queue<std::string> gameMessages;
    std::queue<std::string> gameAnnouncments;

    //single player oriented
    int totalScore; //arbitrary units
    double timeSpent; //seconds
    Player* player;

    int spaceWidth;
    int spaceHeight;

    double *gTick = nullptr; //get timing data

    Map *spaceMap; //get map
    char** space; //holds the game space

    std::vector<Entity*> entityList; //list of all entities

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

    //grab the player object
    void attachPlayer(Player &plyr);

    //add a message to the queue
    void pushMessage(std::string message);

    //display the front message
    std::string popMessage();

    //add an announcement to the queue
    void pushAnnouncement(std::string announcement);

    //display the front announcement
    std::string popAnnouncement();

    //make the game space a void of whatever //mostly for testing
    void voidSpace(char c = '.');

    //get the space sizes <&h,&w>
    std::pair<const int*, const int*> getSpaceDimRefs() const;

    //get the reference for the space
    const char** getSpaceRef() const;

    //run once every game cycle;
    void update();

    ~Game();

private:
    //build the char array for the game space
    void allocateSpace();

    //unbuild the char array for the game space
    void deallocateSpace();

    //take the data from the map into game space
    void propogateMap();
    

};


#endif //GAME_H