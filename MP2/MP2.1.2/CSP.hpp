#ifndef CSP_hpp
#define CSP_hpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <ctime>
#include <map>

#define EMPTY '_'

using namespace std;

/*
 Variables:
 Xi,j, where i = x-axis location, j = y-axis location
 
 Domain:
 different colors ex) {O, B, G, Y, R}
 
 Variable Selection:
 1. Minimum Remaining Value
 -> Reduces the unassigned variable pool by choosing the variables with having smallest domain size
 2. Most Constraining Variable
 -> Reduces the pool even more by choosing the variables with most number adjacent cells that are unassigned
 
 Forward Checking:
 Keep track of the domain for each unassigned variable and if an assignment to be attempted causes
 any adjacent unassigned variable to have empty domain, do not attempt and try other value from domain
 
 Constraints:
 1. Lines cannot cross each other and cannot take a zigzag path
 -> Non-source cells have exactly two neighboring cells with same color
     num of (Cnon-source == {Cu, Cd, Cl, Cr}) -> exactly 2
 -> Source cells have exactly one neighboring cell with same color
     num of (Csource == {Cu, Cd, Cl, Cr}) -> exactly 1
 
 complete assignment means no empty cells
 */

class CSP{
private:
    int nodeCount;
    int width, height;
    vector<char> domain;
    vector<int> sourceLoc;
    map<int, vector<char>> unassignedVar;
    char* grid;
public:
    CSP();
    bool smartSolver();
    bool smartBacktrack(map<int, vector<char>> varAndDomain);
    bool testConsistent(int loc, char val);
    bool checkLocConsistent(int loc) const;
    bool checkComplete() const;
    bool parseGrid(string fileName);
    bool forwardCheck(map<int, vector<char>> varAndDomain) const;
    vector<int> grabAdjacent(int loc) const;
    map<int, vector<char>> minimumRemainingValue(map<int, vector<char>> varAndDomain) const;
    map<int, vector<char>> mostConstrainingVariable(map<int, vector<char>> varAndDomain) const;
    map<int, vector<char>> updateDomain(map<int, vector<char>> varAndDomain, int var);
    int getNodeCount() const;
    void printGrid() const;
    ~CSP();
    //bool smarterSolver();
    //bool smarterBacktrack(map<int, vector<char>> varAndDomain);
    //void arcConsistency();
    //bool removeInconsistentValues(pair<int, vector<char>> xi, pair<int, vector<char>> xj);
    //bool testPairConsistent(int loc1, char val1, int loc2, char val2);
};

#endif
