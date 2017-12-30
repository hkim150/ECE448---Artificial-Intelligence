#include "maze.hpp"

Maze::Maze(){
    width = 0;
    height = 0;
    startX = 0;
    startY = 0;
    goalX = 0;
    goalY = 0;
    map = NULL;
}

Maze::Maze(const Maze& other){
    width = other.getWidth();
    height = other.getHeight();
    startX = other.getStartX();
    startY = other.getStartY();
    goalX = other.getGoalX();
    goalY = other.getGoalY();
    if(other.getMap() == NULL){map = NULL;}
    else{
        map = new char[width * height];
        for(int i=0; i<width*height; i++){
            map[i] = other.map[i];
        }
    }
}

Maze& Maze::operator=(const Maze& other){
    if(this != &other){
        width = other.getWidth();
        height = other.getHeight();
        startX = other.getStartX();
        startY = other.getStartY();
        goalX = other.getGoalX();
        goalY = other.getGoalY();
        if(other.getMap() == NULL){map = NULL;}
        else{
            map = new char[width * height];
            for(int i=0; i<width*height; i++){
                map[i] = other.map[i];
            }
        }
    }
    return *this;
}

int Maze::getWidth() const{return width;}

int Maze::getHeight() const{return height;}

int Maze::getStartX() const{return startX;}

int Maze::getStartY() const{return startY;}

int Maze::getGoalX() const{return goalX;}

int Maze::getGoalY() const{return goalY;}

char* Maze::getMap() const{return map;}

bool Maze::parseMaze(string fileName){
    ifstream inFile;
    
    inFile.open(fileName);
    
    // safety function
    if(!inFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    string line;
    vector<string> tempLine;
    int lineCount = 0;
    int temp = 0;
    
    // parse line by line
    while(getline(inFile, line)){
        tempLine.push_back(line);
        for(int i=0; i<line.size(); i++){
            if(line[i] == START){startX = temp;}
            else if(line[i] == GOAL){goalX = temp;}
            temp++;
        }
        lineCount++;
    }
    
    // store info in private member variables
    width = (int)line.size();
    height = lineCount;
    
    startY = startX/width;
    startX %= width;
    
    goalY = goalX/width;
    goalX %= width;
    
    // store the map as 1D array in heap
    map = new char[width * height];
    
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            map[i*width + j] = tempLine[i].at(j);
        }
    }

    inFile.close();
    
    return true;
}

bool Maze::printMaze() const{
    if(map == NULL){return false;}
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            cout << map[i*width + j];
        }
        cout << endl;
    }
    return true;
}

Maze::~Maze(){
    if(map != NULL){delete map;}
}
