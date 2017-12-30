#ifndef Node_hpp
#define Node_hpp

#include <vector>
#include "Board.hpp"

typedef struct Node{
    Board board;
    vector<Node*> child;
}Node;

#endif
