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

class Search{
private:
    Maze* maze;
    vector<int> explored;
    int step, expandedNode;
public:
    Search(Maze* maze);
    Maze* getMaze() const;              // getters
    int getStep() const;
    int getExpandedNode() const;
    vector<int> getExplored() const;
    void initialize();                  // to be run before performing any search
    bool checkExplored(int loc) const;  // helpers
    bool checkBoundary(int loc) const;
    double findManhattanDist(int loc) const;
    std::pair<int, double> findMinManhattan(map<int, double> m) const;
    std::pair<int, std::pair<int, double>> findMinTotalCost(std::map<int, std::pair<int, double>> m) const;
    int DFS();                          // main search functions
    int BFS();
    int GBFS();
    int AStar();
    ~Search();
};

#endif
