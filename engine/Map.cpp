/*
Implimentation file for Map class

created by levi morris - 12/30/24
*/

#include "Map.h"

Map::Map(std::string fileName) {
    std::string line;
    std::fstream file(pathName + fileName);
    if (!file) {std::cerr << "couldnt open file" << std::endl; throw std::runtime_error("Failed to open file");}

    //get map name
    if (getline(file,line)) {mapName = line;}
    else {mapName = "unnamed";}

    //get author
    if (getline(file,line)) {creator = line;}
    else {creator = "unknown";}

    int maxRow = 0;
    int maxCol = 0;
    while(getline(file,line)) {
        maxRow++;
        maxCol = std::max(int(line.length()), maxCol);
    }

    mapHeight = maxRow;
    mapWidth = maxCol;

    //get the space for the map connected to mapArray
    allocateSpace();

    //go back to 2nd line
    file.clear();
    file.seekg(0, std::ios::beg);
    getline(file,line);
    getline(file,line);

    int row = 0;
    while(getline(file,line)) {
        for (int col = 0; col < mapWidth; col++) {
            if (col < line.length()) {mapArray[row][col] = line[col];}
            else {mapArray[row][col] = 'b';}

            if (line[col] == '@') {mapSpawns.push_back({row,col});}
        }
        row++;
    }

    if(mapSpawns.empty()) {mapSpawns.push_back({0,0});}
}

std::pair<int,int> Map::getDimensions() {
    return std::make_pair(mapHeight, mapWidth);
}

char** Map::getMap() {
    return mapArray;
}

std::vector<std::pair<int,int>> Map::getSpawns() {
    return mapSpawns;
}

Map::~Map() {
    deallocateSpace();
}


//private helper functions

void Map::allocateSpace() {
    //makes a char array such that the map space can be indexed space[r][c]
    mapArray = new char*[mapHeight];
    for (int i = 0; i < mapHeight; i++) {mapArray[i] = new char[mapWidth];}

}

void Map::deallocateSpace() {
    //no more map space
    for (int i = 0; i < mapHeight; i++) {delete[] mapArray[i];}
    delete[] mapArray;
}