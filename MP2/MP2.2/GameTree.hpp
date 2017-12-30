#ifndef Game_hpp
#define Game_hpp

#include <cstdlib>
#include <ctime>
#include "Node.hpp"

class GameTree{
private:
    int totalExpandedNode;
public:
    GameTree();
    Node* makeInitialNode();
    Node* makeNode(Board board);
    Node* makeNode(Board board, vector<Node*> child);
    vector<Node*> getChildren(Node* node, char color);
    vector<pair<int, int>> getNextAvailableLoc(Board board, int x, int y);
    void deleteNode(Node* root);
    void deleteNode(Node* root, Node* child);
    int getTotalExpandedNode() const;
};

#endif
