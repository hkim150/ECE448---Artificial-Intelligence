#include "Bayes.hpp"

int main(){
    /*
    for(double k=0.1; k<10; k+=0.1){
        Bayes naiveBayes;
        cout << k << '\t';
        naiveBayes.parseImage("yes_train.txt", true);
        naiveBayes.parseImage("no_train.txt", false);
        naiveBayes.computePClass();
        naiveBayes.computeLikelihood(k);
        naiveBayes.parseImage("yes_test.txt", true);
        naiveBayes.parseImage("no_test.txt", false);
        naiveBayes.testImages();
        naiveBayes.evaluate();
    }
    */
    
    Bayes naiveBayes;
    naiveBayes.parseImage("yes_train.txt", true);
    naiveBayes.parseImage("no_train.txt", false);
    naiveBayes.computePClass();
    naiveBayes.computeLikelihood(3.35);
    naiveBayes.parseImage("yes_test.txt", true);
    naiveBayes.parseImage("no_test.txt", false);
    naiveBayes.testImages();
    naiveBayes.evaluate();

    return 0;
}
