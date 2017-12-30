#include "maze.hpp"

Maze::Maze(){
    width = 0;
    height = 0;
    startLoc = 0;
    goalLoc.clear();
    map = NULL;
}

Maze::Maze(const Maze& other){
    width = other.getWidth();
    height = other.getHeight();
    startLoc = other.getStartLoc();
    goalLoc.clear();
    for(int i=0; i<other.goalLoc.size(); i++){
        goalLoc.push_back(other.goalLoc[i]);
    }
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
        startLoc = other.getStartLoc();
        goalLoc.clear();
        for(int i=0; i<other.goalLoc.size(); i++){
            goalLoc.push_back(other.goalLoc[i]);
        }
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

int Maze::getStartLoc() const{return startLoc;}
    
vector<int> Maze::getGoalLoc() const{return goalLoc;}
    
char* Maze::getMap() const{return map;}

bool Maze::parseMaze(string fileName){
    ifstream inFile;
    
    inFile.open(fileName);
    
    if(!inFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    string line;
    vector<string> tempLine;
    int lineCount = 0;
    int temp = 0;
    
    while(getline(inFile, line)){
        tempLine.push_back(line);
        for(int i=0; i<line.size(); i++){
            if(line[i] == GOAL){goalLoc.push_back(temp);}
            else if(line[i] == START){startLoc = temp;}
            temp++;
        }
        lineCount++;
    }
    
    width = (int)line.size();
    height = lineCount;
    
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
