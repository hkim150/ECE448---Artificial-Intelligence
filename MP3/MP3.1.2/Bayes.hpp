#ifndef Bayes_hpp
#define Bayes_hpp

#include <fstream>
#include "Image.hpp"

class Bayes{
private:
    vector<Image> image;
    vector<int> guess;
    int classCount[NUM_CLASS] = {};
    double*** p_of_g_given_class = NULL;
    double p_class[NUM_CLASS] = {};
    double confusionMatrix[NUM_CLASS][NUM_CLASS] = {};
public:
    bool parseImage(string imageFileName, string labelFileName);
    void train(double laplace_k);
    void test();
    void evaluate();
    ~Bayes();
};

#endif
