#ifndef MAP_H
#define MAP_H

#include <vector>
#include<string>

class Map {

private:
    char* mapArray;

    //properties
    int mapWidth;
    int mapHeight;

    std::string mapName;
    std::string creator;

    bool checkValid();//helper function

public:

    Map(std::string fileName = "default.txt");

    std::string getMapName();

    std::string getCreator();

};


#endif //MAP_H