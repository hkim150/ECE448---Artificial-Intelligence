#ifndef CSP_hpp
#define CSP_hpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <map>

#define EMPTY '_'

using namespace std;

/*
 Variables:     Xi,j, where i = x-axis location, j = y-axis location
 
 Domain:        different colors, ex) {O, B, G, Y, R}
 
 Constraints:
 non-source cells have exactly two neighboring cells with same color
 num of (Cnon-source == {Cu, Cd, Cl, Cr}) -> exactly 2
 
 source cells have exactly one neighboring cell with same color
 num of (Csource == {Cu, Cd, Cl, Cr}) -> exactly 1
 
 complete assignment means no empty cells
 
 selects random unassigned variable and random value from domain
 worst case (number of unassigned variable)^(size of domain)
 */

class CSP{
private:
    int randSeed, nodeCount;
    int width, height;
    vector<char> domain;
    vector<int> sourceLoc, unassignedVar;
    char* grid;
public:
    CSP();
    bool dumbSolver();
    bool dumbBacktrack();
    int selectRandVariable();
    void selectRandValue(vector<char>* valueOrder);
    void eraseUnassignedVar(int var);
    bool checkConsistent(int loc, char val) const;
    bool checkLocConsistent(int loc, bool sameVal) const;
    bool checkComplete() const;
    bool parseGrid(string fileName);
    void grabAdjacent(int loc, vector<int>* ret) const;
    int getNodeCount() const;
    void printGrid() const;
    ~CSP();
};

#endif
