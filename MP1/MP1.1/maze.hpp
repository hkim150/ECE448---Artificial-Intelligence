/*
 * Maze class parses the txt file and stores
 * the information in its own attributes.
 * This class is used as an attribute in
 * Search class.
 */

#ifndef maze_hpp
#define maze_hpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#define WALL '%'
#define START 'P'
#define PATH ' '
#define GOAL '.'

using namespace std;

class Maze{
private:
    char* map;
    int width, height;
    int startX, startY, goalX, goalY;
public:
    Maze();
    Maze(const Maze& other);                // copy constructor
    Maze& operator=(const Maze& other);     // copy assignment operator
    int getWidth() const;                   // getters
    int getHeight() const;
    int getStartX() const;
    int getStartY() const;
    int getGoalX() const;
    int getGoalY() const;
    char* getMap() const;
    bool parseMaze(string fileName);        // parses txt file and stores the map
    bool printMaze() const;                 // map print function
    ~Maze();
};

#endif
