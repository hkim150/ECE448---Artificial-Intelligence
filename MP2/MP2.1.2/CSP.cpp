#include "CSP.hpp"

CSP::CSP(){
    nodeCount = 0;
    width = 0;
    height = 0;
    grid = NULL;
    domain.clear();
    sourceLoc.clear();
    unassignedVar.clear();
}

bool CSP::smartSolver(){
    nodeCount = 0;
    return smartBacktrack(unassignedVar);
}

bool CSP::smartBacktrack(map<int, vector<char>> varAndDomain){
    if(checkComplete()){return true;}
    
    map<int, vector<char>> reducedVar = minimumRemainingValue(varAndDomain);
    reducedVar = mostConstrainingVariable(reducedVar);
    
    int var = reducedVar.begin()->first;
    vector<char> val = reducedVar.begin()->second;
    
    for(int i=0; i<val.size(); i++){
        if(testConsistent(var, val[i])){
            nodeCount++;
            grid[var] = val[i];
            map<int, vector<char>> newVarAndDomain = updateDomain(varAndDomain, var);
            if(forwardCheck(newVarAndDomain)){
                if(smartBacktrack(newVarAndDomain)){return true;}
            }
            grid[var] = EMPTY;
        }
    }
    return false;
}

// try putting a value in the variable and test consistency
// restore the change and return the boolean
bool CSP::testConsistent(int loc, char val){
    bool flag = true;
    bool ret = false;
    
    char temp = grid[loc];
    grid[loc] = val;
    
    if(checkLocConsistent(loc)){
        vector<int> adjacent = grabAdjacent(loc);
        for(int i=0; i<adjacent.size(); i++){
            if(!checkLocConsistent(adjacent[i])){
                flag = false;
                break;
            }
        }
        ret = flag;
    }
    
    grid[loc] = temp;
    
    return ret;
}

// check if a location is consistent with the constraints
bool CSP::checkLocConsistent(int loc) const{
    char val = grid[loc];
    if(val == EMPTY){return true;}
    
    bool ret = true;
    bool isSource = false;
    
    for(int i=0; i<sourceLoc.size(); i++){
        if(sourceLoc[i] == loc){
            isSource = true;
            break;
        }
    }
    
    int emptyCount = 0;
    int sameValCount = 0;
    
    vector<int> adjacent = grabAdjacent(loc);
    
    for(int i=0; i<adjacent.size(); i++){
        if(grid[adjacent[i]] == EMPTY){emptyCount++;}
        else if(grid[adjacent[i]] == val){sameValCount++;}
    }
    
    if(isSource){
        if(sameValCount > 1){ret = false;}
        else if(sameValCount == 0){
            if(emptyCount < 1){ret = false;}
        }
    }
    else{
        if(sameValCount > 2){ret = false;}
        else if(sameValCount == 1){
            if(emptyCount < 1){ret = false;}
        }
        else if(sameValCount == 0){
            if(emptyCount < 2){ret = false;}
        }
    }
    
    return ret;
}

// check if the remaining unassigned variables have at least 1 remaining value
bool CSP::forwardCheck(map<int, vector<char>> varAndDomain) const{
    for(map<int, vector<char>>::iterator it=varAndDomain.begin(); it!=varAndDomain.end(); ++it){
        if(it->second.empty()){return false;}
    }
    return true;
}

// get adjacent locations
vector<int> CSP::grabAdjacent(int loc) const{
    vector<int> ret;
    
    if(loc%width != 0){ret.push_back(loc-1);}
    if((loc+1)%width != 0){ret.push_back(loc+1);}
    if(loc >= width){ret.push_back(loc - width);}
    if(loc < width*(height-1)){ret.push_back(loc + width);}
    
    return ret;
}

// reduce the variable pool by selecting ones with least number of possible values
map<int, vector<char>> CSP::minimumRemainingValue(map<int, vector<char>> varAndDomain) const{
    map<int, vector<char>> ret;
    int min, numValue;
    min = -1;
    
    for(map<int, vector<char>>::iterator it=varAndDomain.begin(); it!=varAndDomain.end(); ++it){
        numValue = (int)it->second.size();
        if(min == -1){min = numValue;}
        if(min >= numValue){
            if(min > numValue){
                min = numValue;
                ret.clear();
            }
            ret.insert(pair<int, vector<char>>(it->first, it->second));
        }
    }
    return ret;
}

// reduce the variable pool by selecting ones with most number of unassigned adjacent cells
map<int, vector<char>> CSP::mostConstrainingVariable(map<int, vector<char>> varAndDomain) const{
    map<int, vector<char>> ret;
    int max, emptyCount;
    max = -1;
    
    for(map<int, vector<char>>::iterator it=varAndDomain.begin(); it!=varAndDomain.end(); ++it){
        emptyCount = 0;
        vector<int> adjacent = grabAdjacent(it->first);
        for(int j=0; j<adjacent.size(); j++){
            if(grid[adjacent[j]] == EMPTY){emptyCount++;}
        }
        if(max == -1){max = emptyCount;}
        if(max <= emptyCount){
            if(max < emptyCount){
                max = emptyCount;
                ret.clear();
            }
            ret.insert(pair<int, vector<char>>(it->first, it->second));
        }
    }
    return ret;
}

// update the remaining possible values for each unassigned variable
map<int, vector<char>> CSP::updateDomain(map<int, vector<char>> varAndDomain, int var){
    varAndDomain.erase(var);
    vector<int> adjacent = grabAdjacent(var);
    
    for(int i=0; i<adjacent.size(); i++){
        map<int, vector<char>>::iterator it = varAndDomain.find(adjacent[i]);
        
        if(it != varAndDomain.end()){
            vector<char> domain;
            
            domain.operator=(it->second);
            it->second.clear();
            for(int j=0; j<domain.size(); j++){
                if(testConsistent(adjacent[i], domain[j])){it->second.push_back(domain[j]);}
            }
        }
    }
    return varAndDomain;
}

// check if assignment is complete
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
            else{unassignedVar.insert(pair<int, vector<char>>(count, vector<char>()));}
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
    
    for(map<int, vector<char>>::iterator it=unassignedVar.begin(); it!=unassignedVar.end(); ++it){
        for(int i=0; i<domain.size(); i++){
            if(testConsistent(it->first, domain[i])){it->second.push_back(domain[i]);}
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

// extra credit arc consistency work going on
/*
bool CSP::smarterSolver(){
    nodeCount = 0;
    return smarterBacktrack(unassignedVar);
}

bool CSP::smarterBacktrack(map<int, vector<char>> varAndDomain){
    if(checkComplete()){return true;}
    
    map<int, vector<char>> reducedVar = minimumRemainingValue(varAndDomain);
    reducedVar = mostConstrainingVariable(reducedVar);
    
    int var = reducedVar.begin()->first;
    vector<char> val = reducedVar.begin()->second;
    
    for(int i=0; i<val.size(); i++){
        if(testConsistent(var, val[i])){
            nodeCount++;
            grid[var] = val[i];
            map<int, vector<char>> newVarAndDomain = updateDomain(varAndDomain, var);
            arcConsistency();
            if(smarterBacktrack(newVarAndDomain)){return true;}
            grid[var] = EMPTY;
        }
    }
    return false;
}

bool CSP::removeInconsistentValues(pair<int, vector<char>> xi, pair<int, vector<char>> xj){
    vector<char> copy;
    copy.operator=(xi.second);
    bool reduced = false;
    bool found = false;
    
    for(int i=0; i<copy.size(); i++){
        for(int j=0; j<xj.second.size(); j++){
            if(testPairConsistent(xi.first, copy[i], xj.first, xj.second[j])){
                found = true;
                break;
            }
        }
        if(!found){
            for(int k=0; k<xi.second.size(); k++){
                if(xi.second[k] == copy[i]){
                    xi.second.erase(xi.second.begin() + k);
                    reduced = true;
                }
            }
            found = false;
        }
    }
    return reduced;
}


void CSP::arcConsistency(){
    queue<pair<pair<int, vector<char>>, pair<int, vector<char>>>> q;
    for(map<int, vector<char>>::iterator it=unassignedVar.begin(); it!=unassignedVar.end();++it){
        vector<int> adjacent = grabAdjacent(it->first);
        for(int i=0; i<adjacent.size(); i++){
            map<int, vector<char>>::iterator it2 = unassignedVar.find(adjacent[i]);
            if(it2 != unassignedVar.end()){
                q.push(pair<pair<int, vector<char>>, pair<int, vector<char>>>(pair<int, vector<char>>(it->first, it->second), pair<int, vector<char>>(it2->first, it2->second)));
            }
        }
    }
    while(!q.empty()){
        pair<pair<int, vector<char>>, pair<int, vector<char>>> mypair = q.front();
        q.pop();
        if(removeInconsistentValues(mypair.first, mypair.second)){
            vector<int> adjacent2 = grabAdjacent(mypair.first.first);
            for(int i=0; i<adjacent2.size(); i++){
                map<int, vector<char>>::iterator it3 = unassignedVar.find(adjacent2[i]);
                if(it3 != unassignedVar.end()){
                    q.push(pair<pair<int, vector<char>>, pair<int, vector<char>>>(pair<int, vector<char>>(it3->first, it3->second), mypair.first));
                }
            }
        }
    }
}

bool CSP::testPairConsistent(int loc1, char val1, int loc2, char val2){
    bool test = true;
    char temp1 = grid[loc1];
    grid[loc1] = val1;
    
    test = testConsistent(loc2, val2);
    grid[loc1] = temp1;
    
    if(!test){return test;}
    test = true;
    
    char temp2 = grid[loc2];
    grid[loc2] = val2;
    
    test = testConsistent(loc1, val1);
    grid[loc2] = temp2;
    
    return test;
}
 */

