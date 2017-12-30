#include "CSP.hpp"

CSP::CSP(){
    randSeed = (int)time(NULL);
    nodeCount = 0;
    width = 0;
    height = 0;
    grid = NULL;
    domain.clear();
    sourceLoc.clear();
    unassignedVar.clear();
}

bool CSP::dumbSolver(){
    nodeCount = 0;
    return dumbBacktrack();
}

// dumb solver
// depth first search with random selection of variable and value
bool CSP::dumbBacktrack(){
    if(checkComplete()){return true;}

    bool flag;
    int var = selectRandVariable();
    vector<char> valueOrder;
    selectRandValue(&valueOrder);

    for(int i=0; i<valueOrder.size(); i++){
        nodeCount++;
        flag = checkConsistent(var, valueOrder[i]);
        if(flag){
            grid[var] = valueOrder[i];
            eraseUnassignedVar(var);
            
            if(dumbBacktrack()){return true;}
            grid[var] = EMPTY;
            unassignedVar.push_back(var);
        }
    }
    return false;
}

// pick a random variable from the container
int CSP::selectRandVariable(){
    srand(++randSeed);

    return unassignedVar[rand()%unassignedVar.size()];
}

// randomly order the domain before looping
void CSP::selectRandValue(vector<char>* valueOrder){
    srand(++randSeed);
    int randNum;
    
    vector<char> container;
    for(int i=0; i<domain.size(); i++){
        container.push_back(domain[i]);
    }

    while(container.size() > 0){
        randNum = rand()%container.size();
        valueOrder->push_back(container[randNum]);
        container.erase(container.begin() + randNum);
    }
}

void CSP::eraseUnassignedVar(int var){
    for(int i=0; i<unassignedVar.size(); i++){
        if(unassignedVar[i] == var){unassignedVar.erase(unassignedVar.begin() + i);}
    }
}

// checks whether assigning a value on a location is consistent with the constraints
bool CSP::checkConsistent(int loc, char val) const{
    bool ret = true;
    vector<int> adjacent;
    grabAdjacent(loc, &adjacent);
    int emptyCount = 0;
    int sameValCount = 0;
    
    for(int i=0; i<adjacent.size(); i++){
        if(grid[adjacent[i]] == EMPTY){
            emptyCount++;
        }
        else if(grid[adjacent[i]] == val){
            sameValCount++;
            if(!checkLocConsistent(adjacent[i], true) || sameValCount > 2){return false;}
        }
        else{
            if(!checkLocConsistent(adjacent[i], false)){return false;}
        }
    }
    
    if(emptyCount == 1 && sameValCount < 1){ret = false;}
    else if(emptyCount == 0 && sameValCount != 2){ret = false;}
    
    return ret;
}

// checks whether a location is consistent with the constraints
bool CSP::checkLocConsistent(int loc, bool sameVal) const{
    bool ret = true;
    bool isSource = false;
    
    for(int i=0; i<sourceLoc.size(); i++){
        if(sourceLoc[i] == loc){
            isSource = true;
            break;
        }
    }
    
    vector<int> adjacent;
    char val = grid[loc];
    int emptyCount = -1;
    int sameValCount = 0;
    if(sameVal){sameValCount++;}
    grabAdjacent(loc, &adjacent);
    for(int i=0; i<adjacent.size(); i++){
        if(grid[adjacent[i]] == EMPTY){
            emptyCount++;
        }
        else if(grid[adjacent[i]] == val){
            sameValCount++;
            if(isSource && sameValCount > 1){return false;}
            if(!isSource && sameValCount > 2){return false;}
        }
    }
    
    if(!sameVal && isSource){
        if(emptyCount == 0 && sameValCount != 1){ret = false;}
    }
    else if(!sameVal && !isSource){
        if(emptyCount == 1 && sameValCount < 1){ret = false;}
        else if(emptyCount == 0 && sameValCount != 2){ret = false;}
    }
    else if(sameVal && !isSource){
        if(emptyCount == 0 && sameValCount != 2){ret = false;}
    }
    else if(sameVal && isSource){
        if(emptyCount == 0 && sameValCount != 1){ret = false;}
    }

    return ret;
}

// gets the locations of the adjacent cells
void CSP::grabAdjacent(int loc, vector<int>* ret) const{
    if(loc%width != 0){ret->push_back(loc-1);}
    if((loc+1)%width != 0){ret->push_back(loc+1);}
    if(loc >= width){ret->push_back(loc - width);}
    if(loc < width*(height-1)){ret->push_back(loc + width);}
}

// checks whether the assignment is complete
bool CSP::checkComplete() const{
    bool ret = true;
    for(int i=0; i<width*height; i++){
        if(grid[i] == EMPTY){
            ret = false;
            break;
        }
    }
    return ret;
}

int CSP::getNodeCount() const{return nodeCount;}

// parse the grid and store the data
bool CSP::parseGrid(string fileName){
    ifstream myFile;
    
    myFile.open(fileName);
    
    if(!myFile){
        cerr << "Unable to open the file";
        cout << endl;
        return false;
    }
    
    string line;
    vector<string> tempGrid;
    int count = 0;
    
    while(getline(myFile, line)){
        tempGrid.push_back(line);
        for(int i=0; i<line.size(); i++){
            if(line[i] != EMPTY){
                sourceLoc.push_back(count);
                if(domain.empty()){domain.push_back(line[i]);}
                else{
                    for(int j=0; j<domain.size(); j++){
                        if(domain[j] == line[i]){break;}
                        if(j == domain.size() - 1){domain.push_back(line[i]);}
                    }
                }
            }
            else{unassignedVar.push_back(count);}
            count++;
        }
    }
    
    myFile.close();
    
    width = (int)line.size();
    height = (int)tempGrid.size();
    
    grid = new char[width * height];
    
    for(int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            grid[j*width + i] = tempGrid[j].at(i);
        }
    }
    
    return true;
}

void CSP::printGrid() const{
    for(int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            cout << grid[j*height + i];
        }
        cout << endl;
    }
}

CSP::~CSP(){delete grid;}
