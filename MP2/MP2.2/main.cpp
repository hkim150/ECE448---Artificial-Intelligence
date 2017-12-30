#include "Agent.hpp"

int main(){
    //Agent agent1(WHITE, MINIMAX, OFF1), agent2(BLACK, ALPHABETA, OFF1);
    //Agent agent1(WHITE, ALPHABETA, OFF2), agent2(BLACK, ALPHABETA, DEF1);
    //Agent agent1(WHITE, ALPHABETA, DEF2), agent2(BLACK, ALPHABETA, OFF1);
    //Agent agent1(WHITE, ALPHABETA, OFF2), agent2(BLACK, ALPHABETA, OFF1);
    //Agent agent1(WHITE, ALPHABETA, DEF2), agent2(BLACK, ALPHABETA, DEF1);
    Agent agent1(WHITE, ALPHABETA, OFF2), agent2(BLACK, ALPHABETA, DEF2);
    
    Board currBoard;
    clock_t timeStart, timeEnd;
    int pieceCount;
    int agent1MoveCount = 0, agent2MoveCount = 0;
    int agent1CaptureCount = 0, agent2CaptureCount = 0;
    double agent1MakeMoveTime = 0, agent2MakeMoveTime = 0;
    
    while(true){
        pieceCount = currBoard.getPieceCount().second;
        timeStart = clock();
        currBoard= agent1.makeMove();
        timeEnd = clock();
        if(pieceCount != currBoard.getPieceCount().second){agent1CaptureCount++;}
        agent1MakeMoveTime += (double)(timeEnd - timeStart);
        agent1MoveCount++;
        if(currBoard.checkTerminal()){
            cout << "White Win!" << endl;
            break;
        }
        agent2.updateTree(currBoard);
        
        pieceCount = currBoard.getPieceCount().first;
        timeStart = clock();
        currBoard = agent2.makeMove();
        timeEnd = clock();
        if(pieceCount != currBoard.getPieceCount().first){agent2CaptureCount++;}
        agent2MakeMoveTime += (double)(timeEnd - timeStart);
        agent2MoveCount++;
        if(currBoard.checkTerminal()){
            cout << "Black Win!" << endl;
            break;
        }
        agent1.updateTree(currBoard);
    }
    cout << "Final Board:" << endl;
    currBoard.printBoard();
    cout << "Total move count: " << agent1MoveCount + agent2MoveCount << endl;
    cout << "Agent1 total expanded node: " << agent1.getTotalExpandedNode() << endl;
    cout << "Agent2 total expanded node: " << agent2.getTotalExpandedNode() << endl << endl;
    cout << "Agent1 avg expanded node: " << (double)agent1.getTotalExpandedNode()/agent1MoveCount << endl;
    cout << "Agent2 avg expanded node: " << (double)agent2.getTotalExpandedNode()/agent2MoveCount << endl << endl;
    cout << "Agent1 avg time for move: " << agent1MakeMoveTime/CLOCKS_PER_SEC/agent1MoveCount << endl;
    cout << "Agent2 avg time for move: " << agent2MakeMoveTime/CLOCKS_PER_SEC/agent2MoveCount << endl << endl;
    cout << "Agent1 capture count: " << agent1CaptureCount << endl;
    cout << "Agent2 capture count: " << agent2CaptureCount << endl;

    return 0;
}
