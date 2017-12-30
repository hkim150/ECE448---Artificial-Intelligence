#include "search.hpp"
#include <time.h>

using namespace std;

int main(){
    int step;
    Maze* maze = new Maze;
    
    maze->parseMaze("small_search.txt");               /// uncomment to select map
    //maze->parseMaze("small_search.txt");
    //maze->parseMaze("medium_search.txt");
    
    Search search(maze);
    
    clock_t timeStart, timeEnd;
    timeStart = clock();
    
    step = search.BFS();                              /// uncomment to select search method
    //step = search.AStar();
    
    timeEnd = clock();
    
    search.getMaze()->printMaze();
    cout << step << " steps" << endl;
    cout << search.getExpandedNode() << " expanded nodes" << endl;
    cout << "execution time: " << (double)(timeEnd - timeStart)/CLOCKS_PER_SEC << " sec" << endl << endl;
    
    return 0;
}
