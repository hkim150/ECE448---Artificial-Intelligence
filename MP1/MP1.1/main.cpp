#include "search.hpp"
#include <time.h>

using namespace std;

int main(){
    int step;
    Maze* maze = new Maze;
    
    maze->parseMaze("big_maze.txt");                 /// uncomment to select maze
    //maze->parseMaze("medium_maze.txt");
    //maze->parseMaze("big_maze.txt");
    
    Search search(maze);

    clock_t timeStart, timeEnd;
    timeStart = clock();
    
    step = search.DFS();                              /// uncomment to select search method
    //step = search.BFS();
    //step = search.GBFS();
    //step = search.AStar();
    
    timeEnd = clock();
    
    search.getMaze()->printMaze();
    cout << step << " steps" << endl;
    cout << search.getExpandedNode() << " expanded nodes" << endl;
    cout << "execution time: " << (double)(timeEnd - timeStart)/CLOCKS_PER_SEC << " sec" << endl << endl;
    
    return 0;
}
