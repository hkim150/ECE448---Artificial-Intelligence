#include "Board.hpp"

Board::Board(){initialize();}

Board::Board(const Board& other){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            board[i][j] = other.board[i][j];
        }
    }
}

void Board::initialize(){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(i < 2){board[i][j] = BLACK;}
            else if(i > HEIGHT - 3){board[i][j] = WHITE;}
            else{board[i][j] = EMPTY;}
        }
    }
}

char Board::getLocation(int x, int y) const{return board[y][x];}

// move the piece from one location to another, making the previous position empty
void Board::movePiece(int fromX, int fromY, int toX, int toY){
    board[toY][toX] = board[fromY][fromX];
    board[fromY][fromX] = EMPTY;
}

// check if the game is over
bool Board::checkTerminal() const{
    for(int i=0; i<WIDTH; i++){
        if(board[0][i] == WHITE || board[HEIGHT-1][i] == BLACK){return true;}
    }
    pair<int, int> count = getPieceCount();
    if(count.first == 0 || count.second == 0){return true;}
    return false;
}

// return number of pieces of both colors
pair<int, int> Board::getPieceCount() const{
    pair<int, int> ret;
    ret.first = 0;
    ret.second = 0;
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(board[i][j] == WHITE){ret.first++;}
            else if(board[i][j] == BLACK){ret.second++;}
        }
    }
    return ret;
}

// get the piece that is nearest to the goal and find its distance from it
int Board::getClosestDistance(char piece) const{
    if(piece == WHITE){
        for(int i=0; i<HEIGHT-1; i++){
            for(int j=0; j<WIDTH; j++){
                if(board[i][j] == piece){
                    return i;
                }
            }
        }
    }
    else{
        for(int i=HEIGHT-1; i>0; i--){
            for(int j=0; j<WIDTH; j++){
                if(board[i][j] == piece){
                    return HEIGHT - 1 - i;
                }
            }
        }
    }
    return -1;
}

void Board::printBoard() const{
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

Board& Board::operator=(const Board& other){
    if(this != &other){
        for(int i=0; i<HEIGHT; i++){
            for(int j=0; j<WIDTH; j++){
                board[i][j] = other.board[i][j];
            }
        }
    }
    return *this;
}

// overloaded comparing operator for comparing if the pieces and their locations on the board are equal
bool Board::operator==(const Board& other){
    for(int i=0; i<HEIGHT; i++){
        for(int j=0; j<WIDTH; j++){
            if(board[i][j] != other.board[i][j]){return false;}
        }
    }
    return true;
}
