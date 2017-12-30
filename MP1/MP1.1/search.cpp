#include "search.hpp"

Search::Search(Maze* maze){
    step = -1;
    expandedNode = 0;
    explored.clear();
    this->maze = new Maze;
    this->maze->operator=(*maze);
}

int Search::getStep() const{return step;}

int Search::getExpandedNode() const{return expandedNode;}

vector<int> Search::getExplored() const{return explored;}

Maze* Search::getMaze() const{return maze;}

void Search::initialize(){
    step = -1;          // since step is incremented from the start, it is set to -1
    expandedNode = 0;
    explored.clear();
}

int Search::DFS(){
    initialize();
    
    char* map = maze->getMap();
    
    stack<int> frontier;            // stack containing locations to be explored
    
    int current, next;
    int upRightDownLeft[4] = {};    // array containing the locations of four adjacent directions
    
    current = maze->getStartY() * maze->getWidth() + maze->getStartX();
    
    frontier.push(current);
    
    while(!frontier.empty()){
        if(!checkExplored(frontier.top())){
            current = frontier.top();
            map[current] = ',';                 // print , for each step made
            step++;
        }
        frontier.pop();

        if(!checkExplored(current)){
            explored.push_back(current);
            
            upRightDownLeft[0] = current + 1;
            upRightDownLeft[1] = current + maze->getWidth();
            upRightDownLeft[2] = current - 1;
            upRightDownLeft[3] = current - maze->getWidth();
            
            // check four directions and if GOAL, return incremented step count
            for(int i=0; i<4; i++){
                next = upRightDownLeft[i];
                if(checkBoundary(next)){
                    if(map[next] == GOAL){return ++step;}
                }
            }
            
            // check four directions and if PATH, push it in the stack
            for(int i=0; i<4; i++){
                next = upRightDownLeft[i];
                if(checkBoundary(next)){
                    if(!checkExplored(next) && map[next] == PATH){
                        frontier.push(next);
                        expandedNode++;
                    }
                }
            }
        }
    }
    return step;
}

// BFS is almost the same as DFS except that it uses queue instead of stack
int Search::BFS(){
    initialize();
    
    char* map = maze->getMap();
    
    queue<int> frontier;
    
    int current, next;
    int upRightDownLeft[4] = {};
    current = maze->getStartY() * maze->getWidth() + maze->getStartX();
    
    frontier.push(current);
    
    while(!frontier.empty()){
        if(!checkExplored(frontier.front())){
            current = frontier.front();
            map[current] = ',';
            step++;
        }
        frontier.pop();
        
        if(!checkExplored(current)){
            explored.push_back(current);
            
            upRightDownLeft[0] = current + 1;
            upRightDownLeft[1] = current + maze->getWidth();
            upRightDownLeft[2] = current - 1;
            upRightDownLeft[3] = current - maze->getWidth();
            
            for(int i=0; i<4; i++){
                next = upRightDownLeft[i];
                if(checkBoundary(next)){
                    if(map[next] == GOAL){return ++step;}
                }
            }
            
            for(int i=0; i<4; i++){
                next = upRightDownLeft[i];
                if(checkBoundary(next)){
                    if(!checkExplored(next) && map[next] == PATH){
                        frontier.push(next);
                        expandedNode++;
                    }
                }
            }
        }
    }
    return step;
}

int Search::GBFS(){
    initialize();
    
    char* map = maze->getMap();

    std::map<int, double> frontier;                 // container for storing position to be explored
    std::pair<int, double> current, next, temp;     // int is position, double is manhattan distance
    
    int upRightDownLeft[4] = {};
    
    current.first = maze->getStartY() * maze->getWidth() + maze->getStartX();
    current.second = findManhattanDist(current.first);
    
    frontier.insert(current);
    
    while(!frontier.empty()){
        temp = findMinManhattan(frontier);          // choose location in frontier that has minimum manhattan distance
        if(!checkExplored(temp.first)){
            current = temp;
            map[current.first] = ',';
            step++;
        }
        std::map<int, double>::iterator it = frontier.find(temp.first);
        frontier.erase(it);
        
        if(!checkExplored(current.first)){
            explored.push_back(current.first);
            
            upRightDownLeft[0] = current.first + 1;
            upRightDownLeft[1] = current.first + maze->getWidth();
            upRightDownLeft[2] = current.first - 1;
            upRightDownLeft[3] = current.first - maze->getWidth();
            
            // check adjacent four directions and if GOAL, increment step and return
            for(int i=0; i<4; i++){
                next.first = upRightDownLeft[i];
                if(checkBoundary(next.first)){
                    if(map[next.first] == GOAL){return ++step;}
                }
            }
            
            // check adjacent four directions and if PATH, add the position in the frontier
            for(int i=0; i<4; i++){
                next.first = upRightDownLeft[i];
                if(checkBoundary(next.first)){
                    if(!checkExplored(next.first) && map[next.first] == PATH){
                        next.second = findManhattanDist(next.first);
                        frontier.insert(next);
                        expandedNode++;
                    }
                }
            }
        }
    }
    return step;
}

int Search::AStar(){
    initialize();
    
    char* map = maze->getMap();
    
    std::map<int, std::pair<int, double>> frontier;             // container that holds locations to be explored
    std::pair<int, std::pair<int, double>> current, next, temp; // <location, <actual cost up to now, manhattan distance>>
    int upRightDownLeft[4] = {};
    
    current.first = maze->getStartY() * maze->getWidth() + maze->getStartX();
    current.second = std::pair<int, double>(0, findManhattanDist(current.first));
    
    frontier.insert(current);
    
    while(!frontier.empty()){
        temp = findMinTotalCost(frontier);                      // choose location with minimum total cost
        if(!checkExplored(temp.first)){
            current = temp;
            map[current.first] = ',';
            step++;
        }
        std::map<int, std::pair<int, double>>::iterator it = frontier.find(temp.first);
        frontier.erase(it);
        
        if(!checkExplored(current.first)){
            explored.push_back(current.first);
            
            upRightDownLeft[0] = current.first + 1;
            upRightDownLeft[1] = current.first + maze->getWidth();
            upRightDownLeft[2] = current.first - 1;
            upRightDownLeft[3] = current.first - maze->getWidth();
            
            // check adjacent four directions and if GOAL, increment step and return
            for(int i=0; i<4; i++){
                next.first = upRightDownLeft[i];
                if(checkBoundary(next.first)){
                    if(map[next.first] == GOAL){return ++step;}
                }
            }
            
            // check adjacent four directions and if PATH, add the position in the frontier
            for(int i=0; i<4; i++){
                next.first = upRightDownLeft[i];
                if(checkBoundary(next.first)){
                    if(!checkExplored(next.first) && map[next.first] == PATH){
                        next.second.first = current.second.first + 1;
                        next.second.second = findManhattanDist(next.first);
                        frontier.insert(next);
                        expandedNode++;
                    }
                }
            }
        }
    }
    return step;
}

// manhattan distance calculator
double Search::findManhattanDist(int loc) const{
    int x = loc%maze->getWidth();
    int y = loc/maze->getWidth();
    
    double ret = abs(x - maze->getGoalX()) + abs(y - maze->getGoalY());
    
    return ret;
}

// returns element with minimum manhattan distance; used for GBFS
std::pair<int, double> Search::findMinManhattan(std::map<int, double> m) const{
    std::pair<int, double> p;
    p.second = 1000000000.0;            // initial manhattan set large enough so that first element becomes the min
    for(std::map<int, double>::iterator it=m.begin(); it!=m.end(); it++){
        if(it->second < p.second){
            p.second = it->second;
            p.first = it->first;
        }
    }
    return p;
}

// returns element with minimum total cost; used for AStar Search
std::pair<int, std::pair<int, double>> Search::findMinTotalCost(std::map<int, std::pair<int, double>> m) const{
    std::pair<int, std::pair<int, double>> p;
    p.second = std::pair<int, double>(1000000000, 1000000000.0);
    for(std::map<int, std::pair<int, double>>::iterator it=m.begin(); it!= m.end(); it++){
        if(it->second.first + it->second.second < p.second.first + p.second.second){
            p.second.first = it->second.first;
            p.second.second = it->second.second;
            p.first = it->first;
        }
    }
    return p;
}

// check whether the location is within the boundary
bool Search::checkBoundary(int loc) const{
    bool inBoundary = false;
    if(loc >= 0 && loc < maze->getWidth() * maze->getHeight()){inBoundary = true;}
    return inBoundary;
}

// check whether the location has been explored before
bool Search::checkExplored(int loc) const{
    bool found = false;
    for(int i=0; i<explored.size(); i++){
        if(explored[i] == loc){
            found = true;
            break;
        }
    }
    return found;
}

Search::~Search(){
    maze->~Maze();
    maze = NULL;
}
