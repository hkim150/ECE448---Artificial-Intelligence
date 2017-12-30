#ifndef Board_hpp
#define Board_hpp

#include <iostream>
using namespace std;

#define WIDTH 8
#define HEIGHT 8
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY '_'

class Board{
private:
    char board[HEIGHT][WIDTH];
    void initialize();
public:
    Board();
    Board(const Board& other);
    bool checkTerminal() const;
    char getLocation(int x, int y) const;
    void movePiece(int fromX, int fromY, int toX, int toY);
    pair<int, int> getPieceCount() const;
    int getClosestDistance(char piece) const;
    void printBoard() const;
    Board& operator=(const Board& other);
    bool operator==(const Board& other);
};

#endif
