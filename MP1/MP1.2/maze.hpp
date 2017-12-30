/*
 * Maze class parses the txt file and stores
 * the information in its own attributes.
 * This class is used as an attribute in
 * Search class.
 */

#ifndef maze_hpp
#define maze_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#define WALL '%'
#define START 'P'
#define PATH ' '
#define GOAL '.'

using namespace std;

class Maze{
private:
    char* map;
    int width, height;
    int startLoc;
    vector<int> goalLoc;
public:
    Maze();
    Maze(const Maze& other);
    Maze& operator=(const Maze& other);
    int getWidth() const;
    int getHeight() const;
    int getStartLoc() const;
    vector<int> getGoalLoc() const;
    char* getMap() const;
    bool parseMaze(string fileName);
    bool printMaze() const;
    ~Maze();
};

#endif
