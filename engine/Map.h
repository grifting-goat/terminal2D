#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Map {

private:
    char** mapArray = nullptr;
    std::vector<std::pair<int,int>> mapSpawns;

    //properties
    int mapWidth;
    int mapHeight;

    std::string pathName = "C:/Users/onewi/grifting-goat/terminal2D/maps/";

    std::string mapName;
    std::string creator;

    bool checkValid();//helper function

public:

    //construct
    Map(std::string fileName = "default.txt");

    //gettas
    std::string getMapName();

    std::string getCreator();

    //<r.c>
    std::pair<int,int> getDimensions();

    char** getMap();

    //<r.c>
    std::vector<std::pair<int,int>> getSpawns();
    
    //unconstruct
    ~Map();

private:
    //build the char array for the game space
    void allocateSpace();

    //unbuild the char array for the game space
    void deallocateSpace();

};


#endif //MAP_H