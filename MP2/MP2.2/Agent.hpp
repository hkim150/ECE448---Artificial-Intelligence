#ifndef Agent_hpp
#define Agent_hpp

#include "GameTree.hpp"

#define POS_INFINITY __DBL_MAX__
#define NEG_INFINITY __DBL_MIN__

enum{MINIMAX, ALPHABETA};
enum{DEF1, OFF1, DEF2, OFF2};

class Agent{
private:
    char color;
    int method, heuristic;
    unsigned int randSeed;
    Node* currNode;
    GameTree gametree;
public:
    Agent(char color, int method, int heuristic);
    pair<double, Node*> minimax(Node* node, int depthLimit, char pieceColor, bool player);
    pair<double, Node*> alphabeta(Node* node, int depthLimit, double alpha, double beta, char pieceColor, bool player);
    double defensiveHeuristic1(Node* node);
    double offensiveHeuristic1(Node* node);
    double defensiveHeuristic2(Node* node);
    double offensiveHeuristic2(Node* node);
    double chooseHeuristic(Node* node, int heuristic);
    double getRandNum();
    bool updateTree(Board board);
    Board makeMove();
    int getTotalExpandedNode();
};

#endif
