#include <ctime>
#include "Bayes.hpp"

int main(){
    Bayes b;
    
    b.parseImage("training_data.txt", "training_labels.txt");
    time_t trainStart, trainEnd, testStart, testEnd, trainTime, testTime;
    
    trainStart = clock();
    b.train(LAPLACE_K);
    trainEnd = clock();
    
    b.parseImage("testing_data.txt", "testing_labels.txt");
    
    testStart = clock();
    b.test();
    testEnd = clock();
    
    b.evaluate();
    
    trainTime = trainEnd - trainStart;
    testTime = testEnd - testStart;
    
    cout << "Training took: " << (double)trainTime/CLOCKS_PER_SEC << " sec" << endl;
    cout << "Testing took: " << (double)testTime/CLOCKS_PER_SEC << " sec" << endl;
    cout << "Total Running Time: " << (double)(trainTime + testTime)/CLOCKS_PER_SEC << " sec" << endl;
    cout << endl;
    
    return 0;
}

