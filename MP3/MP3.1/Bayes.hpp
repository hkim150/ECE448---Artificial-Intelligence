#ifndef Bayes_hpp
#define Bayes_hpp

#include <queue>
#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>

#include "image.hpp"

using namespace std;

#define NUM_OF_DIGIT 10

class Bayes{
private:
    vector<Image*> image;
    vector<int> digit, guess;
    Image* mostPrototypicalImage[NUM_OF_DIGIT], *leastPrototypicalImage[NUM_OF_DIGIT];
    int digitCount[NUM_OF_DIGIT], highestConfusionRate[4];
    double maxAPosteriori[NUM_OF_DIGIT], minAPosteriori[NUM_OF_DIGIT];
    double p_digit[NUM_OF_DIGIT], p_digit_given_f[NUM_OF_DIGIT], p_f_given_digit[NUM_OF_DIGIT][HEIGHT][WIDTH];
    double confusionMatrix[NUM_OF_DIGIT][NUM_OF_DIGIT];
public:
    Bayes();
    bool parseImage(string fileName);
    bool parseDigit(string fileName);
    void train(string fileName1, string fileName2, double laplace_k);
    void test(string fileName1, string fileName2);
    void evaluate();
    void printLikelihood(int c) const;
    void printOddRatio(int c1, int c2);
    int testImage(Image* img);
};

#endif
