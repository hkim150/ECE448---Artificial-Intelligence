#include "Agent.hpp"

Agent::Agent(char color, int method, int heuristic) : color(color), method(method), heuristic(heuristic){
    currNode = gametree.makeInitialNode();
    gametree.getChildren(currNode, WHITE);
    randSeed = (unsigned int)time(NULL)%100;
}

// given defensive heuristic 1
double Agent::defensiveHeuristic1(Node* node){
    pair<int, int> pieceCount = node->board.getPieceCount();
    double ret = 0.0;
    if(color == WHITE){ret = 2.0*pieceCount.first + getRandNum();}
    else if(color == BLACK){ret = 2.0*pieceCount.second + getRandNum();}
    return ret;
}

// given offensive heuristic 1
double Agent::offensiveHeuristic1(Node* node){
    pair<int, int> pieceCount = node->board.getPieceCount();
    double ret = 0.0;
    if(color == WHITE){ret = 2.0*(30 - pieceCount.second) + getRandNum();}
    else if(color == BLACK){ret = 2.0*(30 - pieceCount.first) + getRandNum();}
    return ret;
}

// added feature of blocking the enemy from reaching the end
double Agent::defensiveHeuristic2(Node* node){
    pair<int, int> pieceCount = node->board.getPieceCount();
    double ret = 0.0;
    if(color == WHITE){ret = 2.0*pieceCount.first + 1.5*(node->board.getClosestDistance(BLACK) - HEIGHT) + getRandNum();}
    else if(color == BLACK){ret = 2.0*pieceCount.second + 1.5*(node->board.getClosestDistance(WHITE) - HEIGHT) + getRandNum();}
    return ret;
}

// added feature of trying to reach the end along with capturing opponent's pieces
double Agent::offensiveHeuristic2(Node* node){
    pair<int, int> pieceCount = node->board.getPieceCount();
    double ret = 0.0;
    if(color == WHITE){ret = 2.0*(30 - pieceCount.second) + (HEIGHT - node->board.getClosestDistance(WHITE)) + getRandNum();}
    else if(color == BLACK){ret = 2.0*(30 - pieceCount.first) + (HEIGHT - node->board.getClosestDistance(BLACK)) + getRandNum();}
    return ret;
}

// utility function that aids in swapping the heuristic in main
double Agent::chooseHeuristic(Node* node, int heuristic){
    double ret = 0.0;
    switch(heuristic){
        case DEF1: ret = defensiveHeuristic1(node);    break;
        case OFF1: ret = offensiveHeuristic1(node);    break;
        case DEF2: ret = defensiveHeuristic2(node);    break;
        case OFF2: ret = offensiveHeuristic2(node);    break;
    }
    return ret;
}

// set the current node as the move selected by the opponent
bool Agent::updateTree(Board board){
    Node* nextNode = NULL;
    for(int i=0; i<currNode->child.size(); i++){
        if(currNode->child[i]->board == board){
            nextNode = currNode->child[i];
            break;
        }
    }
    if(nextNode == NULL){return false;}
    else{
        gametree.deleteNode(currNode, nextNode);
        currNode = nextNode;
    }
    return true;
}

// minimax recursive function
// returns the best heuristic value and the pointer directing to reaching that node
pair<double, Node*> Agent::minimax(Node* node, int depthLimit, char pieceColor, bool player){
    Node* retNode = NULL;
    if(depthLimit == 0 || node->board.checkTerminal()){
        return pair<double, Node*>(chooseHeuristic(node, heuristic), retNode);
    }
    
    double bestHeuristic;
    if(player){bestHeuristic = NEG_INFINITY;}
    else{bestHeuristic = POS_INFINITY;}
    
    if(node->child.empty()){gametree.getChildren(node, pieceColor);}
    char nextPieceColor = WHITE;
    if(pieceColor == WHITE){nextPieceColor = BLACK;}
    for(int i=0; i<node->child.size(); i++){
        pair<double, Node*> result = minimax(node->child[i], depthLimit-1, nextPieceColor, !player);
        if(player){
            if(result.first > bestHeuristic){
                bestHeuristic = result.first;
                retNode = node->child[i];
            }
        }
        else{
            if(result.first < bestHeuristic){
                bestHeuristic = result.first;
                retNode = node->child[i];
            }
        }
    }
    return pair<double, Node*>(bestHeuristic, retNode);
}

// alphabeta recursive function
// returns best heuristic found and the pointer directing to reaching that node
// prunes the nodes by breaking out of the loop
pair<double, Node*> Agent::alphabeta(Node* node, int depthLimit, double alpha, double beta, char pieceColor, bool player){
    Node* retNode = NULL;
    if(depthLimit == 0 || node->board.checkTerminal()){
        return pair<double, Node*>(chooseHeuristic(node, heuristic), retNode);
    }
    
    double bestHeuristic;
    if(player){bestHeuristic = NEG_INFINITY;}
    else{bestHeuristic = POS_INFINITY;}
    
    if(node->child.empty()){gametree.getChildren(node, pieceColor);}
    char nextPieceColor = WHITE;
    if(pieceColor == WHITE){nextPieceColor = BLACK;}
    for(int i=0; i<node->child.size(); i++){
        pair<double, Node*> result = alphabeta(node->child[i], depthLimit-1, alpha, beta, nextPieceColor, !player);
        if(player){
            if(result.first > bestHeuristic){
                bestHeuristic = result.first;
                retNode = node->child[i];
            }
            alpha = max(alpha, bestHeuristic);
        }
        else{
            if(result.first < bestHeuristic){
                bestHeuristic = result.first;
                retNode = node->child[i];
            }
            beta = min(beta, bestHeuristic);
        }
        if(beta <= alpha){break;}
    }
    return pair<double, Node*>(bestHeuristic, retNode);
}

double Agent::getRandNum(){
    randSeed++;
    srand(randSeed);
    return (rand()%1000)/1000.0;
}

// determines what move to make and returns the board with the move applied
Board Agent::makeMove(){
    pair<double, Node*> bestMove;
    switch(method){
        case MINIMAX:   bestMove = minimax(currNode, 3, color, true);   break;
        case ALPHABETA: bestMove = alphabeta(currNode, 4, NEG_INFINITY, POS_INFINITY, color, true);
    }
    
    cout << "best heuristic: " << bestMove.first << endl;
    bestMove.second->board.printBoard();
    cout << endl;
     
    gametree.deleteNode(currNode, bestMove.second);
    currNode = bestMove.second;
    return bestMove.second->board;
}

int Agent::getTotalExpandedNode(){return gametree.getTotalExpandedNode();}
