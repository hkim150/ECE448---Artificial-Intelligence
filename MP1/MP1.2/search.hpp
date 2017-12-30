/*
 * Search class performs the four search algorithms
 * on the map stored in the Maze class, which is its
 * attribute.
 */

#ifndef search_h
#define search_h

#include "maze.hpp"
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

class Search{
private:
    Maze* maze;
    vector<int> explored;
    int step, expandedNode;
public:
    Search(Maze* maze);
    Maze* getMaze() const;                      // getter
    int getStep() const;
    int getExpandedNode() const;
    vector<int> getExplored() const;
    void initialize();                          // to be called before search
    bool checkExplored(int loc) const;          // helper functions
    bool checkBoundary(int loc) const;
    double findManhattanDist(int loc1, int loc2) const;
    int findNearestGoalLoc(int loc, vector<int> goalLoc) const;
    std::pair<int, std::pair<int, double>> findMinTotalCost(std::map<int, std::pair<int, double>> m) const;
    int BFS();
    int AStar();
    ~Search();
};

#endif

