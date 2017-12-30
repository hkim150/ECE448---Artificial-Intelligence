#include <ctime>
#include "Bayes.hpp"

int main(){
    Bayes b;
    
    b.parseImage("trainingimages.txt", "traininglabels.txt");
    time_t trainStart, trainEnd, testStart, testEnd, trainingTime, testingTime;
    
    trainStart = clock();
    b.train(LAPLACE_K);
    trainEnd = clock();
    
    b.parseImage("testimages.txt", "testlabels.txt");
    
    testStart = clock();
    b.test();
    testEnd = clock();
    
    b.evaluate();
    
    
    trainingTime = trainEnd - trainStart;
    testingTime = testEnd - testStart;
    cout << "Training took: " << (double)trainingTime/CLOCKS_PER_SEC << " sec" << endl;
    cout << "Testing took: " << (double)testingTime/CLOCKS_PER_SEC << " sec" << endl;
    cout << "Total Running Time: " << (double)(trainingTime + testingTime)/CLOCKS_PER_SEC << " sec" << endl;
    cout << endl;
    
    return 0;
}
