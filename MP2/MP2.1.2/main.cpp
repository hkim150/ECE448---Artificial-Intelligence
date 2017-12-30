#include "CSP.hpp"

int main(){
    CSP csp;
    
    //csp.parseGrid("5*5_puzzle.txt");
    //csp.parseGrid("7*7_puzzle.txt");
    //csp.parseGrid("8*8_puzzle.txt");
    csp.parseGrid("9*9_puzzle.txt");
    
    time_t timeStart, timeEnd;
    timeStart = clock();
    
    csp.smarterSolver();
    
    timeEnd = clock();
    
    csp.printGrid();
    
    cout << "total attempted node: " << csp.getNodeCount() << endl;
    cout << "execution time: " << (double)(timeEnd - timeStart)/CLOCKS_PER_SEC << " sec" << endl;
    
    return 0;
}
