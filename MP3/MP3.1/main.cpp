#include "Bayes.hpp"

int main(){
    Bayes naiveBayes;
    double laplace_smoothing_k = 0.1;
    
    naiveBayes.train("trainingimages.txt", "traininglabels.txt", laplace_smoothing_k);
    naiveBayes.test("testimages.txt", "testlabels.txt");
    naiveBayes.evaluate();
    
    return 0;
}
