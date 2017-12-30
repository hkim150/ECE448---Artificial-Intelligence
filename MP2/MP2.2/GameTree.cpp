#include "GameTree.hpp"

GameTree::GameTree(){totalExpandedNode = 0;}

Node* GameTree::makeInitialNode(){
    Node* ret = new Node;
    return ret;
}

Node* GameTree::makeNode(Board board){
    Node* newNode = new Node;
    newNode->board = board;
    return newNode;
}

Node* GameTree::makeNode(Board board, vector<Node*> child){
    Node* newNode = makeNode(board);
    newNode->child = child;
    return newNode;
}

// once the next state is determined, delete the parent and siblings
void GameTree::deleteNode(Node* root){
    if(root->child.empty()){delete root;}
    for(int i=0; i<root->child.size(); i++){
        deleteNode(root->child[i]);
    }
}

void GameTree::deleteNode(Node* root, Node* child){
    for(int i=0; i<root->child.size(); i++){
        if(root->child[i] == child){
            root->child.erase(root->child.begin()+i);
            break;
        }
    }
    deleteNode(root);
}

// get possible moves from the current state and make corresponding nodes
vector<Node*> GameTree::getChildren(Node* node, char color){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(node->board.getLocation(j, i) == color){
                vector<pair<int, int>> loc = getNextAvailableLoc(node->board, j, i);
                for(int k=0; k<loc.size(); k++){
                    Board newBoard = node->board;
                    newBoard.movePiece(j, i, loc[k].first, loc[k].second);
                    Node* newNode = makeNode(newBoard);
                    node->child.push_back(newNode);
                }
            }
        }
    }
    totalExpandedNode += (int)node->child.size();
    return node->child;
}

// helper function for finding next possible moves
vector<pair<int, int>> GameTree::getNextAvailableLoc(Board board, int x, int y){
    vector<pair<int, int>> ret;
    int testY = y;
    char piece = board.getLocation(x, y);
    if(piece == EMPTY){return ret;}
    else if(piece == WHITE){
        if(y != 0){testY--;}
        else{return ret;}
    }
    else if(piece == BLACK){
        if(y != HEIGHT-1){testY++;}
        else{return ret;}
    }
    if(board.getLocation(x, testY) == EMPTY){ret.push_back(pair<int, int>(x, testY));}
    if(x != 0){
        if(board.getLocation(x-1, testY) != piece){ret.push_back(pair<int, int>(x-1, testY));}
    }
    if(x != WIDTH-1){
        if(board.getLocation(x+1, testY) != piece){ret.push_back(pair<int, int>(x+1, testY));}
    }
    return ret;
}

int GameTree::getTotalExpandedNode() const{return totalExpandedNode;}
