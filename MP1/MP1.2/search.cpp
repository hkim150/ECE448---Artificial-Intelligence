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
    step = -1;              // since step is incremented from the start, it is set to -1
    expandedNode = 0;
    explored.clear();
}

// BFS is same as one in part 1.1 but this time, the search keeps going until last goal is found
int Search::BFS(){
    initialize();
    
    char* map = maze->getMap();
    
    queue<int> frontier;
    
    int current, next;
    int num = 0;                    // variable to count number of found goals
    int upRightDownLeft[4] = {};
    current = maze->getStartLoc();
    
    frontier.push(current);
    
    while(!frontier.empty()){
        if(!checkExplored(frontier.front())){
            current = frontier.front();
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
                if(checkBoundary(next) && !checkExplored(next)){
                    if(map[next] != WALL){
                        // if it is GOAL, mark the location and check if it was last goal
                        if(map[next] == GOAL){
                            if(num < 10){map[next] = ++num + 47;}
                            else{map[next] = ++num + 86;}
                            // if it was last goal, return incremented step
                            if(num == maze->getGoalLoc().size()){return ++step;}
                            explored.clear();
                        }
                        frontier.push(next);
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
    vector<int> goalLoc = maze->getGoalLoc();
    
    std::map<int, std::pair<int, double>> frontier;
    std::pair<int, std::pair<int, double>> current, next, temp;
    int upRightDownLeft[4] = {};
    int num = 0;
    
    current.first = maze->getStartLoc();
    int nearestGoalLoc = findNearestGoalLoc(current.first, goalLoc);
    current.second = std::pair<int, double>(0, findManhattanDist(current.first, nearestGoalLoc));
    
    frontier.insert(current);

    while(!frontier.empty()){
        current = findMinTotalCost(frontier);
        step++;

        std::map<int, std::pair<int, double>>::iterator it = frontier.find(current.first);
        frontier.erase(it);

        if(!checkExplored(current.first)){
            explored.push_back(current.first);
            
            upRightDownLeft[0] = current.first + 1;
            upRightDownLeft[1] = current.first + maze->getWidth();
            upRightDownLeft[2] = current.first - 1;
            upRightDownLeft[3] = current.first - maze->getWidth();
            
            // check object of adjacent four directions
            for(int i=0; i<4; i++){
                next.first = upRightDownLeft[i];
                if(checkBoundary(next.first)){
                    if(map[next.first] != WALL){
                        // if it is GOAL, remove the goal from the goal location array
                        if(map[next.first] == GOAL){
                            for(int i=0; i<goalLoc.size(); i++){
                                if(goalLoc[i] == next.first){goalLoc.erase(goalLoc.begin() + i);}
                            }
                            // mark the point with number or alphabet
                            if(num < 10){map[next.first] = ++num + 47;}
                            else{map[next.first] = ++num + 86;}
                            // if it was last goal, return incremented step
                            if(goalLoc.empty()){return ++step;}
                            // find next nearest goal location
                            nearestGoalLoc = findNearestGoalLoc(next.first, goalLoc);
                            next.second.first = 0;
                            next.second.second = findManhattanDist(next.first, nearestGoalLoc);
                            // clear the frontier and explored container
                            frontier.clear();
                            explored.clear();
                        }
                        // if it is PATH, increment actual cost and find new manhattan distance and insert in frontier
                        else if(map[next.first] == PATH){
                            next.second.first = current.second.first + 1;
                            next.second.second = findManhattanDist(next.first, nearestGoalLoc);
                        }
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
double Search::findManhattanDist(int loc1, int loc2) const{
    int x1 = loc1%maze->getWidth();
    int y1 = loc1/maze->getWidth();
    int x2 = loc2%maze->getWidth();
    int y2 = loc2/maze->getWidth();
    
    return abs(x1 - x2) + abs(y1 - y2);
}

// nearest goal location from current location finder
// search method is use of manhattan distance
int Search::findNearestGoalLoc(int loc, vector<int> goalLoc) const{
    int currX = loc%maze->getWidth();
    int currY = loc/maze->getWidth();
    int goalX = goalLoc.at(0)%maze->getWidth();
    int goalY = goalLoc.at(0)/maze->getWidth();
    int dist = abs(currX - goalX) + abs(currY - goalY);
    int tempGoalX, tempGoalY, tempDist;
    for(int i=0; i<goalLoc.size(); i++){
        tempGoalX = goalLoc.at(i)%maze->getWidth();
        tempGoalY = goalLoc.at(i)/maze->getWidth();
        tempDist = abs(currX - tempGoalX) + abs(currY - tempGoalY);
        if(tempDist < dist){
            goalX = tempGoalX;
            goalY = tempGoalY;
            dist = tempDist;
        }
    }
    return goalY * maze->getWidth() + goalX;
}

// returns element with minimum total cost;
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

